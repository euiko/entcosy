#ifndef ENTCOSY_CORE_EVENTS_ONENTITYDESTROYED_HPP
#define ENTCOSY_CORE_EVENTS_ONENTITYDESTROYED_HPP

#include "../core/type_registry.hpp"
#include "../entity.hpp"

namespace entcosy
{
    namespace events
    {
        struct OnEntityDestroyed
        {
            OnEntityDestroyed() { }
            OnEntityDestroyed(std::shared_ptr<Entity> entity) : entity(entity) { }

            std::shared_ptr<Entity> entity;

            RTTR_ENABLE();
        };

    } // events
} // entcosy


#endif
