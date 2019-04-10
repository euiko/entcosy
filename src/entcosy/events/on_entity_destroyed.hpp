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
            ENTCOSY_DECLARE_TYPE;

            std::shared_ptr<Entity> entity;
        };

        ENTCOSY_DEFINE_TYPE(OnEntityDestroyed);
    } // events
} // entcosy


#endif