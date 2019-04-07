#ifndef ECS_CORE_TYPEREGISTRY_HPP
#define ECS_CORE_TYPEREGISTRY_HPP

#include <cinttypes>


#define ECS_DECLARE_TYPE public: static ecs::core::TypeRegistry __ecs_type_reg
#define ECS_DEFINE_TYPE(name) ecs::core::TypeRegistry name::__ecs_type_reg

namespace ecs
{
    typedef uint32_t TypeIndex;

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return T::__ecs_type_reg.getIndex();
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

            TypeIndex getIndex() const
            {
                return m_index;
            }

        private:
            static TypeIndex nextIndex;
            TypeIndex m_index;
        };

        TypeIndex TypeRegistry::nextIndex = 1;
    } // core
} // ecs


#endif