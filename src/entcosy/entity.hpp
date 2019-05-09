#ifndef ENTCOSY_ENTITY_HPP
#define ENTCOSY_ENTITY_HPP

#include <iostream>
#include <rttr/type>
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

        void all(typename std::common_type<std::function<void(rttr::type&, rttr::variant&)>>::type callback)
        {
            for(auto& kv: m_components)
            {
                rttr::type containerType = rttr::type::get(*kv.second.get());
                rttr::property prop = containerType.get_property("component");
                rttr::variant value = prop.get_value(*kv.second.get());
                rttr::type realType = value.get_type();
                callback(realType, value);
            }
        }

        template<typename T, typename... TArgs>
        T* assign(TArgs&& ...args)
        {
            rttr::type typeId = rttr::type::get<T>();
            rttr::type::type_id id = typeId.get_id();
            auto found = m_components.find(id);
            if (found != m_components.end())
            {
                std::shared_ptr<core::ComponentContainer<T>> container= std::reinterpret_pointer_cast<core::ComponentContainer<T>> (found->second);
                container->component = { args... };
                return &container->component;
            }
            T component = { args... };
            std::shared_ptr<core::ComponentContainer<T>> container = std::make_shared<core::ComponentContainer<T>>(component);
            m_components.insert({ id, container });

            m_registry->emit<events::OnComponentAssigned<T>>({ shared_from_this(),  &container->component});

            return &container->component;
        }

        template<typename T>
        void remove()
        {
            rttr::type typeId = rttr::type::get<T>();
            auto found = m_components.find(typeId.get_id());
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
            rttr::type typeId = rttr::type::get<T>();
            auto found = m_components.find(typeId.get_id());
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
            rttr::type typeId = rttr::type::get<T>();;
            return m_components.find(typeId.get_id()) != m_components.end();
        }

        template <class Archive>
        void serialize( Archive & ar )
        {
            ar( m_components, m_registry );
        }

    private:
        std::unordered_map<rttr::type::type_id, std::shared_ptr<core::BaseComponentContainer>> m_components;
        TypeIndex m_id;
        core::TypeRegistry m_typeRegistry;
        std::shared_ptr<Registry> m_registry;
        std::string m_name;
    };

} // ecs

#endif
