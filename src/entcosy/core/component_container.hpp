#ifndef ENTCOSY_BASE_COMPONENTCONTAINER_HPP
#define ENTCOSY_BASE_COMPONENTCONTAINER_HPP

#include <rttr/type>
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

            RTTR_ENABLE()
        };

        template<typename T>
        struct ComponentContainer : public BaseComponentContainer
        {
            ComponentContainer() : BaseComponentContainer() {}
            ComponentContainer(const T& component) : BaseComponentContainer(), component(component) { }

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

            RTTR_ENABLE(BaseComponentContainer)
        };
    } // base
} // ecs


#endif
