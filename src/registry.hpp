#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP

#ifdef USE_HPX

    #include <hpx/hpx_init.hpp>
    #include <hpx/hpx.hpp>
    #include <hpx/include/parallel_numeric.hpp>
    #include <hpx/include/parallel_algorithm.hpp>
    #include <hpx/parallel/algorithms/fill.hpp>

    #define std_par hpx::parallel

#elif USE_INTEL_PSTL

    #include <pstl/execution>
    #include <pstl/numeric>
    #include <pstl/algorithm>

    #define std_par std

#else

    // Use the standard library implementation
    // #include <execution>
    #include <numeric>
    #include <algorithm>

    #define std_par std

#endif


#include <vector>
#include <functional>
#include <algorithm>
#include <mutex>

#include "event_subscriber.hpp"
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

        template <typename T>
        void subscribe(EventSubscriber<T> *subscriber)
        {
            TypeIndex typeId = getTypeIndex<T>();
            auto found = m_events.find(typeId);
            if(found == m_events.end()) // There is no event
            {
                std::vector<core::BaseEventSubscriber*> subcriberList;
                subcriberList.push_back(subscriber);
                m_events.insert({ typeId, subcriberList });
            } else
            {
                found->second.push_back(reinterpret_cast<core::BaseEventSubscriber*>(subscriber));
            }
        }
        
        template <typename T>
        void unsubscribe(EventSubscriber<T> *subscriber)
        {
            TypeIndex typeId = getTypeIndex<T>();
            auto found = m_events.find(typeId);
            if(found != m_events.end()) // There is event
            {
                
                found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber));
                if(found->second.size() <= 0)
                {
                    m_events.erase(found);
                }
            }
        }

        template <typename T>        
        void emit(const T &event)
        {
            TypeIndex typeId = getTypeIndex<T>();
            auto found = m_events.find(typeId);
            if(found != m_events.end())
            {
                for(auto *bSubscriber: found->second)
                {
                    EventSubscriber<T> *subscriber = reinterpret_cast<EventSubscriber<T>*>(bSubscriber);
                    subscriber->receive(event); 
                }
            }
        }


        void update(float delta_time);

    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<System>> m_systems;
        std::unordered_map<TypeIndex, std::vector<core::BaseEventSubscriber*>> m_events;
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
        // View<Types...> view = each<Types...>();

        // std::mutex m;
        // std_par::for_each(std_par::execution::par, m_entities.begin(), m_entities.end(), [&](auto entity)
        std::for_each(m_entities.begin(), m_entities.end(), [&](auto entity)
        {
            // std::lock_guard<std::mutex> guard(m);
            if(entity->template has<Types...>())
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