#ifndef ENTCOSY_ENTITY_HPP
#define ENTCOSY_ENTITY_HPP

#include <iostream>
#include <cereal/types/string.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include "events/on_component_assigned.hpp"
#include "events/on_component_removed.hpp"
#include "core/component_container.hpp"
#include "core/type_registry.hpp"

namespace entcosy
{
    class Registry;
    class Entity : public std::enable_shared_from_this<Entity>
    {
    public:
        friend class cereal::access;

        Entity() : m_registry(nullptr)
        {
            m_id = m_typeRegistry.getIndex();
        }

        Entity(std::shared_ptr<Registry> registry, const char* name = "") : m_registry(registry), m_name(name)
        {
            m_id = m_typeRegistry.getIndex();
            if(this->m_name == "")
            {

                this->m_name = "Entity " + std::to_string(m_id);
            }
        }

        TypeIndex getEntityId()
        {
            return m_id;
        }

        const char * getEntityName() const
        {
            return m_name.data();
        }

        template<typename T, typename... TArgs>
        T* assign(TArgs&& ...args)
        {
            TypeIndex typeId = getTypeIndex<T>();
            auto found = m_components.find(typeId);
            if (found != m_components.end())
            {
                std::shared_ptr<core::ComponentContainer<T>> container= std::reinterpret_pointer_cast<core::ComponentContainer<T>> (found->second);
                container->component = { args... };
                return &container->component;
            }
            T component = { args... };
            std::shared_ptr<core::ComponentContainer<T>> container = std::make_shared<core::ComponentContainer<T>>(component);
            m_components.insert({ typeId, container });

            m_registry->emit<events::OnComponentAssigned<T>>({ shared_from_this(),  &container->component});

            return &container->component;
        }

        template<typename T>
        void remove()
        {
            auto found = m_components.find(getTypeIndex<T>());
            if(found != m_components.end())
            {
                std::shared_ptr<core::ComponentContainer<T>> container= std::reinterpret_pointer_cast<core::ComponentContainer<T>> (found->second);
                m_registry->emit<events::OnComponentRemoved>({ shared_from_this(), &container->component });
                m_components.erase(found);
            }
        }

        template<typename T>
        T* get()
		{
			auto found = m_components.find(getTypeIndex<T>());
			if (found != m_components.end())
			{
                std::shared_ptr<core::ComponentContainer<T>> container =
                    std::reinterpret_pointer_cast<core::ComponentContainer<T>> (found->second);

				return &container->component;
			}
			else
			{
				return std::nullptr_t();
			}
        }

        template<typename T, typename K, typename ...Types>
        bool has()
        {
            return has<T>() && has<K, Types...>();
        }


        template<typename T>
        bool has()
        {
            TypeIndex typeId = getTypeIndex<T>();
            return m_components.find(typeId) != m_components.end();
        }

        template <class Archive>
        void serialize( Archive & ar )
        {
            ar( m_components, m_registry );
        }

    private:
        std::unordered_map<TypeIndex, std::shared_ptr<core::BaseComponentContainer>> m_components;
        TypeIndex m_id;
        core::TypeRegistry m_typeRegistry;
        std::shared_ptr<Registry> m_registry;
        std::string m_name;
    };

} // ecs

#endif
