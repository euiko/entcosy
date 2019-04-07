#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include "core/component_container.hpp"
#include "core/type_registry.hpp"

namespace ecs
{
    class Entity
    {
    public:
        Entity() 
        {
            m_id = m_typeRegistry.getIndex();
        }

        TypeIndex getEntityId()
        {
            return m_id;
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

            return &container->component;
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

        ~Entity()
        {
            // for(auto container : m_components)
            // {
            // std::cout << "Desctruction Entity " << m_id << "\n";   
            // }
        }

    private:
        std::unordered_map<TypeIndex, std::shared_ptr<core::BaseComponentContainer>> m_components; 
        TypeIndex m_id;
        core::TypeRegistry m_typeRegistry;

    };
    
} // ecs

#endif