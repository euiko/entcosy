#ifndef ENTCOSY_CORE_EVENTS_ONENTITYCREATED_HPP
#define ENTCOSY_CORE_EVENTS_ONENTITYCREATED_HPP

#include "../core/type_registry.hpp"
#include "../entity.hpp"

namespace entcosy
{
    namespace events
    {
        struct OnEntityCreated
        {
            OnEntityCreated() { }
            OnEntityCreated(std::shared_ptr<Entity> entity) : entity(entity) { }

            std::shared_ptr<Entity> entity;

            RTTR_ENABLE();
        };

    } // events
} // entcosy


#endif
