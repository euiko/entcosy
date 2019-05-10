#ifndef ENTCOSY_CORE_TYPEREGISTRY_HPP
#define ENTCOSY_CORE_TYPEREGISTRY_HPP

#include <cereal/types/polymorphic.hpp>
#include <rttr/type>
#include <rttr/registration>
#include <string>
#include <cinttypes>

namespace entcosy
{
    namespace core
    {
        class TypeRegistry; // Forward declaration to fix numerous error due to incomplete class definition
    } // core
} // entcosy



// #define ENTCOSY_DECLARE_TYPE public: static entcosy::core::TypeRegistry __ENTCOSY_type_reg
#define ENTCOSY_DECLARE_TYPE

// #define ENTCOSY_REGISTER_TYPE(name) entcosy::core::TypeRegistry name::__ENTCOSY_type_reg("name")
#define ENTCOSY_DEFINE_TYPE(name) rttr::registration::class_<entcosy::core::ComponentContainer<name>>("entcosy::core::ComponentContainer<" #name ">") \
        .constructor<>() ( rttr::policy::ctor::as_std_shared_ptr ) \
        .constructor<name&>() \
        .property("component", &entcosy::core::ComponentContainer<name>::component) ( rttr::policy::prop::bind_as_ptr );

#define ENTCOSY_SERIALIZATION_REGISTER(name) CEREAL_REGISTER_TYPE(entcosy::core::ComponentContainer<name>); \
    CEREAL_REGISTER_POLYMORPHIC_RELATION(entcosy::core::BaseComponentContainer, entcosy::core::ComponentContainer<name>)

#define ENTCOSY_BEGIN_DEFINE ENTCOSY_DEFINE_TYPE(entcosy::tags::UiCompTag)

#define ENTCOSY_INITIALIZATION entcosy::TypeIndex entcosy::core::TypeRegistry::nextIndex = 1; \
	ENTCOSY_SERIALIZATION_REGISTER(entcosy::tags::UiCompTag) \
	//
	// ENTCOSY_REGISTER_TYPE(entcosy::events::OnEntityCreated);
	// ENTCOSY_REGISTER_TYPE(entcosy::events::OnEntityDestroyed);
namespace entcosy
{
    typedef uint32_t TypeIndex;

	template<typename T>
	const TypeIndex getTypeIndex()
	{
		return T::__ENTCOSY_type_reg.getIndex();
    }

    template<class name>
	const char * getTypeName()
	{
		return "Unregistered class";
    }

    namespace core
    {
        class TypeRegistry
        {
        public:
            TypeRegistry()
            {
                m_index = nextIndex;
                ++nextIndex;
            }

            TypeRegistry(const char * name ) : m_name(name)
            {
                m_index = nextIndex;
                ++nextIndex;
            }

            TypeIndex getIndex() const
            {
                return m_index;
            }

            const char * getName() const
            {
                return m_name.data();
            }

        private:
            static TypeIndex nextIndex;
            TypeIndex m_index;
            std::string m_name;
        };

        // TypeIndex TypeRegistry::nextIndex = 1;
    } // core
} // ecs

#endif
