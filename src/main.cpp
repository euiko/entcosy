#include <iostream>
#include <vector>
#include <deque>
#include "registry.hpp"

struct PlayerTag
{
    ECS_DECLARE_TYPE;
};

struct PositionComponent
{
    ECS_DECLARE_TYPE;
    int x, y;
    PositionComponent(int x, int y) : x(x), y(y)
    {
        
    }
};
ECS_DEFINE_TYPE(PlayerTag);
ECS_DEFINE_TYPE(PositionComponent);

// ecs::TypeIndex ecs::core::TypeRegistry::nextIndex = 1;
// ecs::core::TypeRegistry ecs::Entity::__ecs_type_reg;
int main()
{
    ecs::Registry registry;
    // std::vector<ecs::Entity> entities;
    std::shared_ptr<ecs::Entity> entity = registry.create();
    entity->assign<PositionComponent>(rand()%10, 1);
    entity->assign<PlayerTag>();
    for(int i = 0; i < 100; i++)
    {
        std::shared_ptr<ecs::Entity> entity = registry.create();
        entity->assign<PositionComponent>(rand()%10, 1);
        // entity.assign<PositionComponent>(rand()%10, rand()%20);
        // entities.push_back(entity);
    }
    size_t i = 0;
    registry.each<PositionComponent, PlayerTag>([&](std::shared_ptr<ecs::Entity> entity,
        std::shared_ptr<PositionComponent> pc, std::shared_ptr<PlayerTag> pt)
    {
         std::cout << "Entity Id " << entity->getEntityId() << ": " << pc->x << ", " << pc->y << "("<< pc.use_count() << ")" << "\n";
    });

}