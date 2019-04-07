#ifndef ECS_BASE_COMPONENTCONTAINER_HPP
#define ECS_BASE_COMPONENTCONTAINER_HPP

#include "base_component_container.hpp"

namespace ecs
{
    namespace core
    {
        template<typename T>
        struct ComponentContainer : public BaseComponentContainer
        {
            ComponentContainer() {}
            ComponentContainer(const T& component) : component(component) { }

            T component;

        };
    } // base
} // ecs


#endif