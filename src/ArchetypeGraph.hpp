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
    std::shared_ptr<Node> getOrCreateNodes(const ArchetypeSignature &signature);

public:
    template <typename... Components>
    class CompositeArchetypeView
    {
        class iterator : public std::iterator<
                             std::input_iterator_tag,    // iterator_category
                             std::tuple<Components &...> // value_type
                             >
        {
        private:
            typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator m_current;
            std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>> &m_archetypeViews;
            typename std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>>::iterator m_currentView;
            typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator m_currentViewEnd;

        public:
            explicit iterator(typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator current,
                              std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>> &archetypeViews,
                              typename std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>>::iterator currentView) : m_current(current), m_archetypeViews(archetypeViews), m_currentView(currentView), m_currentViewEnd(currentView == archetypeViews.end() ? typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator(std::make_tuple((std::make_shared<typename std::vector<Components>::iterator>(nullptr))...)) : (*currentView).end()) {}
            iterator &operator++()
            {
                ++m_current;
                
                if (m_current == m_currentViewEnd)
                {
                    m_currentView++;
                    if (m_currentView != m_archetypeViews.end())
                    {
                        m_currentViewEnd = m_currentView->end();
                        m_current = m_currentView->begin();
                    }
                }

                return *this;
            }
            iterator operator++(int)
            {
                iterator retval = *this;
                ++(*this);
                return retval;
            }
            bool operator==(iterator &other) const { return m_current == other.m_current; }
            bool operator!=(iterator &other) const { return !(*this == other); }
            std::tuple<Components &...> operator*() { return *m_current; }
        };

    private:
        std::vector<HeterogeneousContainer::HeterogeneousContainerView<Components...>> m_archetypeViews;
        iterator _begin()
        {
            for (auto view = m_archetypeViews.begin(); view != m_archetypeViews.end(); ++view)
            {
                auto end = view->end();
                if (view->begin() != end)
                    return iterator(view->begin(), m_archetypeViews, view);
            }

            return iterator(m_archetypeViews.size() == 0 ? typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator(std::make_tuple((std::make_shared<typename std::vector<Components>::iterator>(nullptr))...)) : m_archetypeViews.back().end(), m_archetypeViews, m_archetypeViews.end());
        }

    public:
        CompositeArchetypeView(std::set<std::shared_ptr<Archetype>> &archetypes)
        {
            for (auto archetype : archetypes)
                m_archetypeViews.push_back(archetype->getPartialEntities<Components...>());
        };
        iterator begin() { return _begin(); }
        iterator end() { return iterator(m_archetypeViews.size() == 0 ? typename HeterogeneousContainer::HeterogeneousContainerView<Components...>::iterator(std::make_tuple((std::make_shared<typename std::vector<Components>::iterator>(nullptr))...)) : m_archetypeViews.back().end(), m_archetypeViews, m_archetypeViews.end()); }
    };

    ArchetypeGraph();
    std::shared_ptr<Archetype> getArchetype(const ArchetypeSignature &signature);
    template <typename... Components>

    void addEntity(EntityId id, Components... components);
    template <typename Component>
    Component &getComponent(EntityId id);
    template <typename Component>
    void deleteComponent(EntityId id);

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

inline std::shared_ptr<Node> ArchetypeGraph::getOrCreateNodes(const ArchetypeSignature &signature)
{
    auto node = m_root;
    ArchetypeSignature currentSignature;

    for (auto componentId : signature)
    {
        currentSignature.emplace(componentId);
        node = getOrCreateNode(node, currentSignature, componentId);
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

template <typename Component>
inline Component &ArchetypeGraph::getComponent(EntityId id)
{
    assert(m_entitiesRecords.count(id) != 0 && "No entity found with this id!");

    auto record = m_entitiesRecords.at(id);
    return record.archetypeNode->getArchetype()->getComponents<Component>()[record.componentsIndex];
}

template <typename Component>
inline void ArchetypeGraph::deleteComponent(EntityId id)
{
    assert(m_entitiesRecords.count(id) != 0 && "No entity record found with this id!");

    auto &entityRecord = m_entitiesRecords.at(id);
    auto currentSignature = entityRecord.archetypeNode->getArchetype()->computeSignature();
    auto componentId = Type::getId<Component>();

    assert(currentSignature.find(componentId) != currentSignature.end() && "This entity does not have this component!");

    currentSignature.erase(componentId);

    auto toNode = getOrCreateNodes(currentSignature);

    if (!toNode->getArchetype())
        toNode->setArchetype(entityRecord.archetypeNode->getArchetype()->reduce<Component>());


    entityRecord.archetypeNode = toNode;
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
    auto archetypes = getCompatibleArchetypes<Components...>();
    return CompositeArchetypeView<Components...>(archetypes);
}

#endif // ARCHETYPEGRAPH_H_INCLUDED
