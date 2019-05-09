#ifndef ENTCOSY_CORE_EVENTS_ONCOMPONENTREMOVED_HPP
#define ENTCOSY_CORE_EVENTS_ONCOMPONENTREMOVED_HPP

#include "../core/type_registry.hpp"
#include "../entity.hpp"

namespace entcosy
{
    namespace events
    {

        template<typename T>
        struct OnComponentRemoved
        {
            OnComponentRemoved() { }
            OnComponentRemoved(std::shared_ptr<Entity> entity, T* component) : entity(entity), component(component) { }

            std::shared_ptr<Entity> entity;
            std::shared_ptr<T> component;

            RTTR_ENABLE();
        };
    } // events
} // entcosy


#endif
