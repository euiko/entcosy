#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include "registry.hpp"

struct PlayerTag
{
    ECS_DECLARE_TYPE;
};

struct EnemyTag
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
ECS_DEFINE_TYPE(EnemyTag);
ECS_DEFINE_TYPE(PositionComponent);

// ecs::TypeIndex ecs::core::TypeRegistry::nextIndex = 1;
// ecs::core::TypeRegistry ecs::Entity::__ecs_type_reg;
int main()
{
    ecs::Registry registry;
    // std::vector<ecs::Entity> entities;
    for(int i = 0; i < 999999; i++)
    {
        std::shared_ptr<ecs::Entity> entity = registry.create();
        entity->assign<PositionComponent>(rand()%10, 1);
        // entity.assign<PositionComponent>(rand()%10, rand()%20);
        // entities.push_back(entity);
    }
    { 
        std::shared_ptr<ecs::Entity> entity = registry.create();
        entity->assign<PositionComponent>(rand()%10, 1);
        entity->assign<PlayerTag>();
    }
    {
        std::shared_ptr<ecs::Entity> entity = registry.create();
        entity->assign<PositionComponent>(rand()%10, 1);
        entity->assign<EnemyTag>();
    }
    // std::cout << "Halo";
    double start = clock();
    double end;
    double cpuTime;
    while (1)
    {
        end = clock();
        cpuTime =  (end - start) / (CLOCKS_PER_SEC);
        std::mutex m;

        registry.each<PositionComponent>([&](std::shared_ptr<ecs::Entity> entity,
            PositionComponent* pc)
        {
            std::lock_guard lock(m);
            pc->y = 10;
            std::cout << "Entity " << entity->getEntityId() << "\n";
        });
        start = clock();
        std::cout << "Time " << cpuTime << "\n";
    }

    // registry.each<PositionComponent>([&](std::shared_ptr<ecs::Entity> entity,
    //     PositionComponent* pc)
    // {
    //      std::cout << "Entity Id " << entity->getEntityId() << ": " << pc->x << ", " << pc->y << "("<< 1 << ")" << "\n";
    // });
    
    // registry.each<PositionComponent, PlayerTag>([&](std::shared_ptr<ecs::Entity> entity,
    //     std::shared_ptr<PositionComponent> pc, std::shared_ptr<PlayerTag> pt)
    // {
    //      std::cout << "Entity Id " << entity->getEntityId() << ": " << pc->x << ", " << pc->y << "("<< pc.use_count() << ")" << "\n";
    // });
    // registry.each<PositionComponent, EnemyTag>([&](std::shared_ptr<ecs::Entity> entity,
    //     std::shared_ptr<PositionComponent> pc, std::shared_ptr<EnemyTag> et)
    // {
    //      std::cout << "Entity Id " << entity->getEntityId() << ": " << pc->x << ", " << pc->y << "("<< pc.use_count() << ")" << "\n";
    // });
    // std::cout << "Halo";

}