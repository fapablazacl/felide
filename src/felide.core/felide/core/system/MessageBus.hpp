
#ifndef __FELIDE_SYSTEM_MESSAGEBUS_HPP__
#define __FELIDE_SYSTEM_MESSAGEBUS_HPP__

#include <memory>

namespace felide {
    class Component;

    struct Message {
        Component *sender;
        Component *receiver;
    };

    /**
     * @brief Message communication bus for doing inter-component communication
     */
    class MessageBus {
    public:
        virtual ~MessageBus();

        virtual void postMessage(const Message *msg) = 0;

        virtual void connect(Component *component) = 0;

        virtual void disconnect(Component *component) = 0;

    public:
        static std::unique_ptr<MessageBus> create();
    };
}

#endif
