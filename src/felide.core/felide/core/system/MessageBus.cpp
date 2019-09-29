
#include "MessageBus.hpp"

#include "Component.hpp"
#include <set>

namespace felide {
    class MessageBusImpl : public MessageBus {
    public:
        MessageBusImpl() {}

        ~MessageBusImpl() {}

        virtual void postMessage(const Message *msg) override {
            for (Component *component : componentSet) {
                component->handleMessage(msg);
            }
        }

        virtual void connect(Component *component) override {
            componentSet.insert(component);
        }

        virtual void disconnect(Component *component) override {
            componentSet.erase(component);
        }

    private:
        std::set<Component*> componentSet;
    };
}

namespace felide {
    MessageBus::~MessageBus() {}

    std::unique_ptr<MessageBus> MessageBus::create() {
        return std::make_unique<MessageBusImpl>();
    }
}
