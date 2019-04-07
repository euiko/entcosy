#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP

#include <vector>
#include <functional>
#include <algorithm>

#include "entity.hpp"

namespace ecs
{

    class System;
    template<typename ...Types>
    class View;

    class Registry
    {
    public:
        std::shared_ptr<Entity> create()
        {
            std::shared_ptr<Entity> entity = std::make_shared<Entity>();
            m_entities.push_back(entity);
            return entity;
        }

        template<typename... Types>
        void each(typename std::common_type<std::function<void(std::shared_ptr<Entity>, Types*...)>>::type callback);

        template<typename... Types>
        View<Types...> each();

        size_t getCount() const
        {
            return m_entities.size();
        }

        std::shared_ptr<Entity> getByIndex(size_t index)
        {
            if(index >= getCount())
                return nullptr;
            return m_entities[index];
        }

        void update(float delta_time);

    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<System>> m_systems;
    };
} // ecs

#include "view.hpp"
#include "system.hpp"

namespace ecs
{
    template<typename... Types>
    inline View<Types...> Registry::each()
    {
        core::EntityComponentIterator<Types...> first(this, 0, false);
        core::EntityComponentIterator<Types...> last(this, getCount(), true);
        return View<Types...>(first, last);
    }

    template<typename... Types>
    void Registry::each(typename std::common_type<std::function<void(std::shared_ptr<Entity>, Types*...)>>::type callback)
    {
        View<Types...> view = each<Types...>();
        std::for_each(view.begin(), view.end(), [&](auto entity)
        {
            callback(entity, entity->template get<Types>()...);
        } );
    }

    void Registry::update(float delta_time)
    {
        std::for_each(m_systems.begin(), m_systems.end(), [&](auto system)
        {
            system->update(this, delta_time);
        });
    }
} // ecs


#endif