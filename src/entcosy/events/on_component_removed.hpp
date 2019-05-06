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
            ENTCOSY_DECLARE_TYPE;

            std::shared_ptr<Entity> entity;
            std::shared_ptr<T> component;
        };

		template<typename T>
        ENTCOSY_REGISTER_TYPE(OnComponentRemoved<T>);
    } // events
} // entcosy


#endif
