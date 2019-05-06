#ifndef ENTCOSY_EVENTSUBSCRIBER_HPP
#define ENTCOSY_EVENTSUBSCRIBER_HPP

#include "registry.hpp"
#include "core/base_event_subscriber.hpp"

namespace entcosy
{
    class Registry;
    template <typename T>
    class EventSubscriber : public core::BaseEventSubscriber
    {
    public:
        virtual void receive(std::shared_ptr<Registry> registry, const T &event) { }
    };
} // ecs


#endif
