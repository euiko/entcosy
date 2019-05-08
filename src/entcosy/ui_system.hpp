#ifndef ENTCOSY_UISYSTEM_HPP
#define ENTCOSY_UISYSTEM_HPP

#include <cassert>
#include "entity.hpp"
#include "core/base_ui_system.hpp"

namespace entcosy
{

    template<typename T>
    class UiSystem : public core::BaseUiSystem
    {

        virtual void updateUi(std::shared_ptr<Registry> registry, T* ui_state, float delta_time) { }

        virtual void configureUi(std::shared_ptr<Registry> registry, std::shared_ptr<Entity> entity) { }

        TypeIndex getUiStateId() const
        {
            return getTypeIndex<T>();
        }

        void configure(std::shared_ptr<Registry> registry)
        {
            assert(getTypeIndex<T>());
            std::shared_ptr<Entity> entity = registry->create();
            entity->assign<tags::UiCompTag>();
            entity->assign<T>();
            configureUi(registry, entity);
        }
        void update(std::shared_ptr<Registry> registry, float delta_time)
        {
            T* uiState;
            registry->each<T>([&](std::shared_ptr<Entity> entity, T* ui_state)
            {
                uiState = ui_state;
            });
            updateUi(registry, uiState, delta_time);
        }
    };
} // namespace entcosy


#endif
