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
            ENTCOSY_DECLARE_TYPE;

            std::shared_ptr<Entity> entity;
        };

    } // events
} // entcosy


#endif