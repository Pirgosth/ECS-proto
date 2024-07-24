#include <algorithm>
#include <iostream>

#include "Archetype.hpp"
#include "ArchetypeGraph.hpp"
#include "TypeId.hpp"
#include "HeterogeneousContainer.hpp"

// int main()
// {
//     HeterogeneousContainer c1;

//     c1.addContainer<int>();
//     c1.get<int>().push_back(1);

//     c1.addContainer<float>();
//     c1.get<float>().push_back(9.26);

//     auto c2 = c1.clone();

//     c1.get<int>().push_back(27);
//     c1.get<float>().push_back(5.219);

//     for (auto [i, f]: c1.getView<int, float>())
//     {
//         std::cout << i << ";" << f << std::endl;
//     }

//     c2.copy(c1, 0);

//     c2.get<int>().push_back(3);
//     c2.get<float>().push_back(57.298);

//     for (auto [i, f]: c2.getView<int, float>())
//     {
//         std::cout << i << ";" << f << std::endl;
//     }

//     std::cout << "c2 size: " << c2.size() << std::endl;

//     Archetype arch = Archetype::build<int, float, char>();
// }

// int main()
// {
//     Node root = Node::root();

//     auto &components = root.getOrCreateNode<int>()->getArchetype()->getComponents<int>();
//     components.push_back(std::make_shared<int>(1));
//     components.push_back(std::make_shared<int>(45));
//     components.push_back(std::make_shared<int>(92));

//     for (auto i : root.getOrCreateNode<int>()->getArchetype()->getComponents<int>())
//     {
//         std::cout << *i << std::endl;
//     }
// }

// int main()
// {
//     Archetype first = Archetype::build<int>();

//     auto second = first.extend<float>();

//     second.getComponents<int>().push_back(std::make_shared<int>(1));
//     second.getComponents<float>().push_back(std::make_shared<float>(53.94));

//     for (auto [i, f] : second.getPartialEntities<int, float>())
//     {
//         std::cout << *i << ";" << *f << std::endl;
//     }
// }

// int main()
// {
//     Node root = Node::root();
//     auto first = root.getOrCreateNode<int>();

//     first->getArchetype()->getComponents<int>().push_back(std::make_shared<int>(4));
//     first->getArchetype()->getComponents<int>().push_back(std::make_shared<int>(2478));

//     auto second = first->getOrCreateNode<float>();
//     second->getArchetype()->getComponents<int>().push_back(std::make_shared<int>(1));
//     second->getArchetype()->getComponents<int>().push_back(std::make_shared<int>(52));
    
//     second->getArchetype()->getComponents<float>().push_back(std::make_shared<float>(95.25));
//     second->getArchetype()->getComponents<float>().push_back(std::make_shared<float>(284.7));

//     std::cout << "First archetype iteration (int):" << std::endl;

//     for (auto i : first->getArchetype()->getComponents<int>())
//     {
//         std::cout << *i << std::endl;
//     }

//     std::cout << "Second archetype iteration (int, float):" << std::endl;

//     for (auto [i, f] : second->getArchetype()->getPartialEntities<int, float>())
//     {
//         std::cout << *i << ";" << *f << std::endl;
//     }
// }

int main()
{
    ArchetypeGraph graph;
    graph.addEntity(0, 1, 4.25f);
    graph.addEntity(1, 4, 219.3f);
    graph.addEntity(2, 29, 32.28f);
    graph.addEntity(3, 45);
    graph.addEntity(4, false, 45, 92.1f);

    auto signature = Type::getSignature<std::shared_ptr<int>, std::shared_ptr<float>>();
    auto archetype = graph.getArchetype(signature);
    auto test = archetype->computeSignature();

    for (auto [i, f] : archetype->getPartialEntities<std::shared_ptr<int>, std::shared_ptr<float>>())
    {
        std::cout << *i << ";" << *f << std::endl;
    }

    signature = Type::getSignature<std::shared_ptr<int>>();
    archetype = graph.getArchetype(signature);

    for (auto i : archetype->getComponents<std::shared_ptr<int>>())
    {
        std::cout << *i << std::endl;
    }

    auto compatibleArchetypes = graph.getCompatibleArchetypes<std::shared_ptr<int>, std::shared_ptr<float>>();

    for (auto [i, f]: graph.query<std::shared_ptr<int>, std::shared_ptr<float>>())
    {}
}