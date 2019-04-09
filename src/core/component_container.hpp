#ifndef ECS_BASE_COMPONENTCONTAINER_HPP
#define ECS_BASE_COMPONENTCONTAINER_HPP

#include <iostream>

namespace ecs
{
    namespace core
    {
        struct BaseComponentContainer
        {
            virtual ~BaseComponentContainer() {}
        }; 
        
        template<typename T>
        struct ComponentContainer : public BaseComponentContainer
        {
            ComponentContainer() {}
            ComponentContainer(const T& component) : component(component) { }

            T component;

            ~ComponentContainer()
            {
                // std::cout << "Desctruction Component " << T::__ecs_type_reg.getIndex() << "\n";   
            }

        };
    } // base
} // ecs


#endif