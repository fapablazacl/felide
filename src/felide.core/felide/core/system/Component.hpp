
#ifndef __FELIDE_SYSTEM_COMPONENT_HPP__
#define __FELIDE_SYSTEM_COMPONENT_HPP__

namespace felide {
    struct Message;
    class MessageBus;

    /**
     * @brief A Component that sends and receives messages from another (unknown) components
     */
    class Component {
    public:
        Component(MessageBus *messageBus);

        virtual ~Component();

        virtual void handleMessage(const Message *message) = 0;

    protected:
        MessageBus* getBus() const;

    private:
        MessageBus *messageBus;
    };
}

#endif
