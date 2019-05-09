#ifndef ENTCOSY_CORE_BASEUISYSTEM_HPP
#define ENTCOSY_CORE_BASEUISYSTEM_HPP

#include <rttr/type>
#include "../system.hpp"
#include "../tags/ui_comp_tag.hpp"

namespace entcosy
{
    namespace core
    {
        class BaseUiSystem : public System
        {
        public:
            ~BaseUiSystem() { }
            virtual void renderUi(std::shared_ptr<Registry> registry) = 0;
            virtual std::string getUiName() const = 0;
            virtual rttr::type getUiStateType() const = 0;
        };
    } // namespace core
} // namespace entcosy


#endif
