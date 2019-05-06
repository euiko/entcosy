#ifndef ENTCOSY_BASE_COMPONENTCONTAINER_HPP
#define ENTCOSY_BASE_COMPONENTCONTAINER_HPP

#include <iostream>
#include <cereal/types/polymorphic.hpp>

namespace entcosy
{
    namespace core
    {
        struct BaseComponentContainer
        {
            virtual ~BaseComponentContainer() {}

            template<class Archive>
            void serialize(Archive &ar)
            {

            }
        };

        template<typename T>
        struct ComponentContainer : public BaseComponentContainer
        {
            ComponentContainer() {}
            ComponentContainer(const T& component) : component(component) { }

            T component;

            ~ComponentContainer()
            {
                // std::cout << "Desctruction Component " << T::__ENTCOSY_type_reg.getIndex() << "\n";
            }

            template<class Archive>
            void serialize(Archive &ar)
            {
                ar(component);
            }

        };
    } // base
} // ecs


#endif
