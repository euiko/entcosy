#ifndef ENTCOSY_CORE_TYPEREGISTRY_HPP
#define ENTCOSY_CORE_TYPEREGISTRY_HPP

#include <cereal/types/polymorphic.hpp>
#include <string>
#include <cinttypes>

namespace entcosy
{
    namespace core
    {
        class TypeRegistry; // Forward declaration to fix numerous error due to incomplete class definition
    } // core
} // entcosy



#define ENTCOSY_DECLARE_TYPE public: static entcosy::core::TypeRegistry __ENTCOSY_type_reg

#define ENTCOSY_REGISTER_TYPE(name) entcosy::core::TypeRegistry name::__ENTCOSY_type_reg("name")

#define ENTCOSY_DEFINE_COMPONENT_EVENTS(name) template<> ENTCOSY_REGISTER_TYPE(entcosy::events::OnComponentAssigned<name>); \
    template<> ENTCOSY_REGISTER_TYPE(entcosy::events::OnComponentRemoved<name>)

#define ENTCOSY_DEFINE_TYPE(name) ENTCOSY_REGISTER_TYPE(name); \
    CEREAL_REGISTER_TYPE(entcosy::core::ComponentContainer<name>); \
    CEREAL_REGISTER_POLYMORPHIC_RELATION(entcosy::core::BaseComponentContainer, entcosy::core::ComponentContainer<name>) \

#define ENTCOSY_INITIALIZATION \
	entcosy::TypeIndex entcosy::core::TypeRegistry::nextIndex = 1; \
	\
	ENTCOSY_REGISTER_TYPE(entcosy::events::OnEntityCreated); \
	ENTCOSY_REGISTER_TYPE(entcosy::events::OnEntityDestroyed); \
	ENTCOSY_DEFINE_TYPE(entcosy::tags::UiCompTag);

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
