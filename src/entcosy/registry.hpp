#ifndef ENTCOSY_REGISTRY_HPP
#define ENTCOSY_REGISTRY_HPP

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

#include <algorithm>
#include <mutex>
#include <rttr/type>
#include <cereal/types/functional.hpp>
#include <cereal/types/memory.hpp>
#include <unordered_map>
#include <cereal/types/vector.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/binary.hpp>

#include "core/type_registry.hpp"
#include "tags/ui_comp_tag.hpp"
#include "event_subscriber.hpp"

namespace entcosy
{
    // BEGIN FORWARD
    class System;
    template<typename T>
    class UiSystem;
    template<typename ...Types>
    class View;
    class Entity;
    namespace events
    {
        struct OnEntityCreated;
        struct OnEntityDestroyed;
    } // events
    namespace core
    {
        class BaseUiSystem;
    } // namespace core

    // END FORWARD

    class Registry : public std::enable_shared_from_this<Registry>
    {
    public:
        friend class cereal::access;

        Registry() { }

        ~Registry()
        {
            std::cout << "Registry destroyed\n";
        }

        template <typename T>
        void subscribe(EventSubscriber<T> *subscriber)
        {
            rttr::type typeId = rttr::type::get<T>();
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
            auto found = m_events.find(rttr::type::get<T>());
            if(found != m_events.end()) // There is event
            {

                found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber));
                if(found->second.size() <= 0)
                {
                    m_events.erase(found);
                }
            }
        }

        void unsubscribeAll(void *subscriber)
        {
            for(auto &kv : m_events)
            {
                kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber));
                if(kv.second.size() <= 0)
                {
                    m_events.erase(kv.first);
                }
            }
        }

        template<typename T>
        void emit(const T& event)
        {
            auto found = m_events.find(rttr::type::get<T>());
            if(found != m_events.end())
            {
                for(auto *bSubscriber: found->second)
                {
                    EventSubscriber<T> *subscriber = reinterpret_cast<EventSubscriber<T>*>(bSubscriber);
                    subscriber->receive(shared_from_this(), event);
                }
            }
        }

        std::shared_ptr<Entity> create(const char* name = "");

        void destroy(std::shared_ptr<Entity> entity);

        void clear()
        {
            m_entities.clear();
        }

        void all(typename std::common_type<std::function<void(std::shared_ptr<Entity>)>>::type callback);

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

        template<typename T>
        void changeUi();

        template<typename T>
        bool isUiActive();

        void changeUiByName(const std::string &name);

        void registerUi(std::shared_ptr<core::BaseUiSystem> ui_system);

        void registerSystem(std::shared_ptr<System> system);

        void unregisterSystem(std::shared_ptr<System> system);

        void update(float delta_time);

        void renderUi();

        template <class Archive>
        void serialize( Archive & ar )
        {
            ar( m_entities );
        }

    private:
        std::string m_activeUiName;
        std::vector<std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<System>> m_systems;
        std::unordered_map<rttr::type, std::shared_ptr<core::BaseUiSystem>> m_uiSystems;
        std::unordered_map<rttr::type, std::vector<core::BaseEventSubscriber*>> m_events;

        // RTTR_ENABLE();
        // RTTR_REGISTRATION_FRIEND;
    };
} // ecs

#include "view.hpp"
#include "system.hpp"
#include "events/on_entity_destroyed.hpp"
#include "events/on_entity_created.hpp"
#include "entity.hpp"
#include "ui_system.hpp"

namespace entcosy
{

    inline std::shared_ptr<Entity> Registry::create(const char* name)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(shared_from_this(), name);
        m_entities.push_back(entity);
        // events::OnEntityCreated event = {entity};
        emit<events::OnEntityCreated>({ entity });
        return entity;
    }

    inline void Registry::destroy(std::shared_ptr<Entity> entity)
    {
        if(entity.get() == nullptr)
            return;

        emit<events::OnEntityDestroyed>({ entity });
        m_entities.erase(std::remove(m_entities.begin(), m_entities.begin(), entity), m_entities.end());
    }

    template<typename... Types>
    inline View<Types...> Registry::each()
    {
        core::EntityComponentIterator<Types...> first(shared_from_this(), 0, false);
        core::EntityComponentIterator<Types...> last(shared_from_this(), getCount(), true);
        return View<Types...>(first, last);
    }

    template<typename... Types>
    inline void Registry::each(typename std::common_type<std::function<void(std::shared_ptr<Entity>, Types*...)>>::type callback)
    {
        View<Types...> view = each<Types...>();
        std::for_each(view.begin(), view.end(), [&](auto entity)
        {
            callback(entity, entity->template get<Types>()...);
        });
    }
    inline void Registry::all(typename std::common_type<std::function<void(std::shared_ptr<Entity>)>>::type callback)
    {
        std::for_each(m_entities.begin(), m_entities.end(), [&](std::shared_ptr<Entity> entity)
        {
            callback(entity);
        });
    }

    inline void Registry::update(float delta_time)
    {
        std::for_each(m_systems.begin(), m_systems.end(), [&](auto system)
        {
            system->update(shared_from_this(), delta_time);
        });

        if(m_activeUiName != "")
        {
            auto found = m_uiSystems.find(rttr::type::get_by_name(m_activeUiName));
            if(found != m_uiSystems.end())
            {
                found->second->update(shared_from_this(), delta_time);
            }
        }
    }

    inline void Registry::renderUi()
    {
        if(m_activeUiName != "")
        {
            auto found = m_uiSystems.find(rttr::type::get_by_name(m_activeUiName));
            if(found != m_uiSystems.end())
            {
                found->second->renderUi(shared_from_this());
            }
        }
    }

    template<typename T>
    inline void Registry::changeUi()
    {
        rttr::type uiStateType = rttr::type::get<T>();
        auto found = m_uiSystems.find(uiStateType);
        if(found != m_uiSystems.end())
        {
            m_activeUiName = uiStateType.get_name().data();
        }
    }

    template<typename T>
    inline bool Registry::isUiActive()
    {
        return rttr::type::get<T>() == rttr::type::get_by_name(m_activeUiName) ? true : false;
    }

    inline void Registry::changeUiByName(const std::string &name)
    {
        for(auto &kv : m_uiSystems)
        {
            if(kv.second->getUiName() == name)
            {
                m_activeUiName = kv.first.get_name().data();
            }
        }
    }

    inline void Registry::registerUi(std::shared_ptr<core::BaseUiSystem> ui_system)
    {
        ui_system->configure(shared_from_this());
        rttr::type uiStateType = ui_system->getUiStateType();
        if(m_uiSystems.size() == 0)
        {
            m_activeUiName = uiStateType.get_name().data();
        }
        m_uiSystems.insert({uiStateType, ui_system});
    }

    inline void Registry::registerSystem(std::shared_ptr<System> system)
    {
        m_systems.push_back(system);
        system->configure(shared_from_this());
    }

    inline void Registry::unregisterSystem(std::shared_ptr<System> system)
    {
        m_systems.erase( std::remove(m_systems.begin(), m_systems.end(), system), m_systems.end());
        system->unconfigure(shared_from_this());
    }
} // ecs


#endif
