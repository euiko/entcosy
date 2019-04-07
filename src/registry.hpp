#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP

#include <vector>
#include <functional>
#include <algorithm>

#include "entity.hpp"

namespace ecs
{
    class Registry
    {
    public:
        std::shared_ptr<Entity> create()
        {
            std::shared_ptr<Entity> entity = std::make_shared<Entity>();
            m_entities.push_back(entity);
            return entity;
        }

        template<typename... T>
        void each(typename std::common_type<std::function<void(std::shared_ptr<Entity>, T*...)>>::type callback)
        {
            std::for_each( m_entities.begin(), m_entities.end(), [&](auto entity)
            {
                if(entity->template has<T...>())
                    callback(entity, entity->template get<T>()...);
            } );
        }

    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
    };
} // ecs

#endif