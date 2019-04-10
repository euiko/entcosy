#ifndef ENTCOSY_CORE_TYPEREGISTRY_HPP
#define ENTCOSY_CORE_TYPEREGISTRY_HPP

#include <cinttypes>

#define ENTCOSY_DECLARE_TYPE public: static entcosy::core::TypeRegistry __ENTCOSY_type_reg
#define ENTCOSY_DEFINE_TYPE(name) entcosy::core::TypeRegistry name::__ENTCOSY_type_reg

namespace entcosy
{
    typedef uint32_t TypeIndex;

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return T::__ENTCOSY_type_reg.getIndex();
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