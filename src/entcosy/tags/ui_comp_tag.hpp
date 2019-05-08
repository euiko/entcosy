#ifndef ENTCOSY_TAGS_UICOMPTAG_HPP
#define ENTCOSY_TAGS_UICOMPTAG_HPP

#include "../core/type_registry.hpp"

namespace entcosy
{
    namespace tags
    {
        struct UiCompTag
        {
            ENTCOSY_DECLARE_TYPE;

            TypeIndex id;
            std::string name;

            UiCompTag()
            {
                id = m_typeRegistry.getIndex();
            }

            UiCompTag(const std::string &name) : name(name)
            {
                id = m_typeRegistry.getIndex();
            }

        private:
            core::TypeRegistry m_typeRegistry;
        };
    } // namespace tags

} // namespace entcosy


#endif
