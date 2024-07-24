#ifndef ARCHETYPEGRAPH_H_INCLUDED
#define ARCHETYPEGRAPH_H_INCLUDED

#include "Archetype.hpp"
#include "TypeId.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>

class Node;
class ArchetypeGraph;

class Node
{
    friend ArchetypeGraph;

private:
    std::shared_ptr<Archetype> m_archetype;
    std::unordered_map<TypeId, std::shared_ptr<Node>> m_leaves;
    Node() = default;
    void setArchetype(Archetype archetype);

public:
    static Node build();
    static Node root();
    std::tuple<bool, std::shared_ptr<Node>> getOrCreateNode(TypeId componentId);
    std::shared_ptr<Node> getNode(TypeId id);
    std::shared_ptr<Archetype> getArchetype();
};

inline void Node::setArchetype(Archetype archetype)
{
    m_archetype = std::make_shared<Archetype>(archetype);
}

inline Node Node::build()
{
    auto builder = Node();
    builder.m_archetype = nullptr;
    return builder;
}

inline std::tuple<bool, std::shared_ptr<Node>> Node::getOrCreateNode(TypeId componentId)
{
    bool isNew = false;
    if (m_leaves.count(componentId) == 0)
    {
        isNew = true;
        m_leaves.emplace(componentId, std::make_shared<Node>(Node::build()));
    }
    return std::make_tuple(isNew, m_leaves.at(componentId));
}

struct EntityRecord
{
    std::shared_ptr<Node> archetypeNode;
    unsigned int componentsIndex;

    EntityRecord(std::shared_ptr<Node> archetypeNode, unsigned int componentsIndex) : archetypeNode(archetypeNode), componentsIndex(componentsIndex) {};
};
typedef struct EntityRecord EntityRecord;

class ArchetypeGraph
{
private:
    std::shared_ptr<Node> m_root;
    std::unordered_map<EntityId, EntityRecord> m_entitiesRecords;
    std::unordered_map<TypeId, std::set<std::shared_ptr<Node>>> m_componentArchetypes;
    std::shared_ptr<Node> getOrCreateNode(std::shared_ptr<Node> parent, const ArchetypeSignature &signature, TypeId componentId);

public:
    template <typename... Components>
    class CompositeArchetypeView
    {
        class iterator : public std::iterator<
                             std::input_iterator_tag,  // iterator_category
                             std::tuple<Components...> // value_type
                             >
        {
        private:
            std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> current;
            std::set<HeterogeneousContainer::HeterogeneousContainerView<Components...>> &archetypeViews;
            typename std::set<HeterogeneousContainer::HeterogeneousContainerView<Components...>>::iterator currentView;

            template <typename T>
            void incrementContainerIterator(std::shared_ptr<typename std::vector<T>::iterator> &iterator)
            {
                ++(*iterator);
            }

            void incrementContainerIterators(std::shared_ptr<typename std::vector<Components>::iterator>... containerIterators)
            {
                (incrementContainerIterator<Components>(containerIterators), ...);
            }

            template <typename T>
            T retrieveValue(std::shared_ptr<typename std::vector<T>::iterator> iterator)
            {
                return *(*iterator);
            }

            std::tuple<Components...> retrieveValues()
            {
                return std::make_tuple(retrieveValue<Components>(std::get<std::shared_ptr<typename std::vector<Components>::iterator>>(current))...);
            }

            template <typename First, typename... Tail>
            bool equals(iterator other) const
            {
                return *(std::get<0>(current)) == *(std::get<0>(other.current));
            }

        public:
            explicit iterator(std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> current,
                              std::set<HeterogeneousContainer::HeterogeneousContainerView<Components...>> &archetypeViews,
                              typename std::set<HeterogeneousContainer::HeterogeneousContainerView<Components...>>::iterator currentView) : current(current), archetypeViews(archetypeViews), currentView(currentView) {}
            iterator &operator++()
            {
                if (*(std::get<0>(current)) == (*currentView).end())
                {
                    currentView++;
                    current = currentView.begin();
                }
                incrementContainerIterators(std::get<std::shared_ptr<typename std::vector<Components>::iterator>>(current)...);
                return *this;
            }
            iterator operator++(int)
            {
                iterator retval = *this;
                ++(*this);
                return retval;
            }
            bool operator==(iterator other) const { return equals<Components...>(other); }
            bool operator!=(iterator other) const { return !(*this == other); }
            std::tuple<Components...> operator*() { return retrieveValues(); }
        };

    private:
        std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>> m_archetypeViews;

        std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _begin()
        {
            typename std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>>::iterator archetypeView = m_archetypeViews.begin();
            return *(*archetypeView).begin();
        }

        std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _end()
        {
            return *(m_archetypeViews.back()).end();
        }

    public:
        CompositeArchetypeView(std::set<std::shared_ptr<Archetype>> archetypes)
        {
            for (auto archetype : archetypes)
                m_archetypeViews.push_back(archetype->getPartialEntities<Components...>());
        };
        iterator begin() { return iterator(_begin(), m_archetypeViews, m_archetypeViews.begin()); }
        iterator end() { return iterator(_end(), m_archetypeViews, m_archetypeViews.back()); }
    };

    ArchetypeGraph();
    std::shared_ptr<Archetype> getArchetype(const ArchetypeSignature &signature);
    template <typename... Components>
    void addEntity(EntityId id, Components... components);
    template <typename... Components>
    std::set<std::shared_ptr<Archetype>> getCompatibleArchetypes();
    template <typename... Components>
    CompositeArchetypeView<Components...> query();
};

inline std::shared_ptr<Node> ArchetypeGraph::getOrCreateNode(std::shared_ptr<Node> parent, const ArchetypeSignature &signature, TypeId componentId)
{
    auto [isNew, node] = parent->getOrCreateNode(componentId);
    if (isNew)
    {
        for (auto id : signature)
        {
            if (m_componentArchetypes.count(id) == 0)
                m_componentArchetypes.emplace(id, std::set<std::shared_ptr<Node>>());

            auto &nodes = m_componentArchetypes.at(id);
            nodes.emplace(node);
        }
    }
    return node;
}

template <typename... Components>
inline void ArchetypeGraph::addEntity(EntityId id, Components... components)
{
    auto node = m_root;
    auto signature = Type::getSignature<std::shared_ptr<Components>...>();

    ArchetypeSignature currentSignature;

    for (auto componentId : signature)
    {
        currentSignature.emplace(componentId);
        node = getOrCreateNode(node, currentSignature, componentId);
    }

    if (!node->getArchetype())
        node->setArchetype(Archetype::build<std::shared_ptr<Components>...>());

    auto componentsIndex = node->getArchetype()->push_back(std::make_shared<Components>(std::move(components))...);
    m_entitiesRecords.emplace(id, EntityRecord(node, componentsIndex));
}

template <typename... Components>
inline std::set<std::shared_ptr<Archetype>> ArchetypeGraph::getCompatibleArchetypes()
{
    std::set<std::shared_ptr<Node>> compatibleNodes;
    std::set<std::shared_ptr<Archetype>> compatibleArchetypes;

    auto signature = Type::getSignature<Components...>();

    // First lookup to avoid computing heavy set intersection if at least one component is missing
    for (auto componentId : signature)
    {
        if (m_componentArchetypes.count(componentId) == 0)
            return std::set<std::shared_ptr<Archetype>>();
    }

    for (auto componentId : signature)
    {
        auto archetypes = m_componentArchetypes.at(componentId);
        std::set<std::shared_ptr<Node>> mergedCandidates;

        if (componentId == *signature.begin())
            mergedCandidates = archetypes;
        else
            std::set_intersection(compatibleNodes.begin(), compatibleNodes.end(), archetypes.begin(), archetypes.end(), std::inserter(mergedCandidates, mergedCandidates.begin()));

        compatibleNodes = mergedCandidates;
    }

    for (auto node : compatibleNodes)
    {
        if (node->getArchetype())
            compatibleArchetypes.emplace(node->getArchetype());
    }

    return compatibleArchetypes;
}

template <typename... Components>
inline ArchetypeGraph::CompositeArchetypeView<Components...> ArchetypeGraph::query()
{
    return CompositeArchetypeView<Components...>(getCompatibleArchetypes<Components...>());
}

#endif // ARCHETYPEGRAPH_H_INCLUDED
