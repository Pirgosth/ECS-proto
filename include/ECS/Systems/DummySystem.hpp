#ifndef DUMMYSYSTEM_H_INCLUDED
#define DUMMYSYSTEM_H_INCLUDED

#include <iostream>

#include "../System.hpp"

class DummySystem : public System<int>
{
private:
    
public:
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<int>> &entities) override;
};

#endif // DUMMYSYSTEM_H_INCLUDED