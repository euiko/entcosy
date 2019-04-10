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
            ENTCOSY_DECLARE_TYPE;

            std::shared_ptr<Entity> entity;
            T* component;
        };

		template<typename T>
        ENTCOSY_DEFINE_TYPE(OnComponentAssigned<T>);
    } // events
} // entcosy


#endif