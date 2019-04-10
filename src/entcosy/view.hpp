#ifndef ENTCOSY_VIEW_HPP
#define ENTCOSY_VIEW_HPP

#include "core/entity_component_iterator.hpp"

namespace entcosy
{
    template<typename ...Types>
    class View
    {
    public:
        View(const core::EntityComponentIterator<Types...> &firstIteration, const core::EntityComponentIterator<Types...> &lastIteration)
            : m_firstIteration(firstIteration), m_lastIteration(lastIteration) 
        {
            if (m_firstIteration.get() == nullptr || !m_firstIteration.get()->template has<Types...>())
            {
                ++m_firstIteration;
            }
        }

        
        const core::EntityComponentIterator<Types...>& begin() const
        {
            return m_firstIteration;
        }

        core::EntityComponentIterator<Types...>& begin()
        {
            return m_firstIteration;
        }

        const core::EntityComponentIterator<Types...>& end() const
        {
            return m_lastIteration;
        }

        core::EntityComponentIterator<Types...>& end()
        {
            return m_lastIteration;
        }
    private:
        core::EntityComponentIterator<Types...> m_firstIteration;
        core::EntityComponentIterator<Types...> m_lastIteration;

    };
} // ecs


#endif