#ifndef ECS_CORE_ENTITYCOMPONENTITERATOR_HPP
#define ECS_CORE_ENTITYCOMPONENTITERATOR_HPP

#include <cstdint>
#include <memory>
#include "../registry.hpp"
#include "../entity.hpp"

namespace ecs
{
    namespace core
    {
        template<typename ...Types>
        class EntityComponentIterator
        {
        public:
            EntityComponentIterator(Registry* registry, size_t index, bool is_end)
                : m_registry(registry), m_index(index), m_isEnd(is_end)
            {
                
            }

            size_t getIndex() const
            {
                return m_index;
            }

            bool isEnd() const
            {
                return m_isEnd || m_index >= m_registry->getCount();
            }

            std::shared_ptr<Entity> get() const
            {
                if(isEnd())
                    return nullptr;
                return m_registry->getByIndex(m_index);
            }

            std::shared_ptr<Entity> operator*() const
            {
                return get();
            }

            bool operator==(const EntityComponentIterator<Types...> &other)
            {
                if(m_registry != other.m_registry)
                    return false;
                if(isEnd())
                    return other.isEnd();

                return m_index == other.m_index;
            }

            bool operator!=(const EntityComponentIterator<Types...> &other)
            {
                if(m_registry != other.m_registry)
                    return true;
                if(isEnd())
                    return !other.isEnd();

                return m_index != other.m_index;
            }

            EntityComponentIterator<Types...> &operator++()
            {
                ++m_index;
                while (m_index < m_registry->getCount() && (get() == nullptr || !get()->template has<Types...>()))
                {
                    ++m_index;
                }

                if (m_index >= m_registry->getCount())
                    m_isEnd = true;

                return *this;
            }

            EntityComponentIterator<Types...> &operator+(const size_t &v)
            {
                m_index += v;
                while (m_index < m_registry->getCount() && (get() == nullptr || !get()->template has<Types...>()))
                {
                    ++m_index;
                }
                if (m_index >= m_registry->getCount())
                    m_isEnd = true;

                return *this;
            }

        private:
            bool m_isEnd;
            size_t m_index;
            Registry* m_registry;
        };
    } // core
} // ecs

#endif