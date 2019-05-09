#ifndef ENTCOSY_UISYSTEM_HPP
#define ENTCOSY_UISYSTEM_HPP

#include <cassert>
#include <rttr/type>
#include "entity.hpp"
#include "core/base_ui_system.hpp"

namespace entcosy
{

    template<typename T>
    class UiSystem : public core::BaseUiSystem
    {
    public:
        virtual void configureUi(std::shared_ptr<Registry> registry, std::shared_ptr<Entity> entity) { }
        virtual void updateUi(std::shared_ptr<Registry> registry, T* ui_state, float delta_time) { }

        rttr::type getUiStateType() const
        {
            return rttr::type::get<T>();
        }

        void configure(std::shared_ptr<Registry> registry)
        {
            assert(getTypeIndex<T>());
            std::shared_ptr<Entity> entity = registry->create();
            entity->assign<tags::UiCompTag>();
            entity->assign<T>();
            configureUi(registry, entity);
        }

        T* getUiState(std::shared_ptr<Registry> registry)
        {
            T* uiState = nullptr;
            registry->each<T>([&](std::shared_ptr<Entity> entity, T* ui_state)
            {
                uiState = ui_state;
            });
            assert(uiState != nullptr);
            return uiState;
        }

        void update(std::shared_ptr<Registry> registry, float delta_time)
        {
            updateUi(registry, getUiState(registry), delta_time);
        }

        virtual void renderUi(std::shared_ptr<Registry> registry) { }
    };
} // namespace entcosy


#endif
