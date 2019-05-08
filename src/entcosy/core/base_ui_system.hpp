#ifndef ENTCOSY_CORE_BASEUISYSTEM_HPP
#define ENTCOSY_CORE_BASEUISYSTEM_HPP

#include "../system.hpp"
#include "../tags/ui_comp_tag.hpp"

namespace entcosy
{
    namespace core
    {
        class BaseUiSystem : public System
        {
            ~BaseUiSystem() { }
            virtual void configureUi(std::shared_ptr<Registry> registry) = 0;
            virtual void updateUi(std::shared_ptr<Registry> registry) = 0;
            virtual std::string getUiName() const = 0;
            virtual TypeIndex getUiStateId() const = 0;
        };
    } // namespace core
} // namespace entcosy


#endif