#ifndef ENTCOSY_CORE_EVENTS_ONCOMPONENTASSIGNED_HPP
#define ENTCOSY_CORE_EVENTS_ONCOMPONENTASSIGNED_HPP

#include "../core/type_registry.hpp"
#include "../entity.hpp"

namespace entcosy
{
    namespace events
    {

        template<typename T>
        struct OnComponentAssigned
        {
            OnComponentAssigned() { }
            OnComponentAssigned(std::shared_ptr<Entity> entity, T* component) : entity(entity), component(component) { }

            std::shared_ptr<entcosy::Entity> entity;
            T* component;

            RTTR_ENABLE();
        };

    } // events
} // entcosy


#endif
