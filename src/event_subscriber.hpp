#ifndef ENTCOSY_EVENT_SUBSCRIBER_HPP
#define ENTCOSY_EVENT_SUBSCRIBER_HPP

#include "registry.hpp"
#include "core/base_event_subscriber.hpp"

namespace ecs
{
    class Registry;
    template <typename T>
    class EventSubscriber : core::BaseEventSubscriber
    {
    public:
        virtual void receive(Registry &registry, const T &event) { }
    };
} // ecs


#endif