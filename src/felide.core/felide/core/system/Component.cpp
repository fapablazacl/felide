
#include "Component.hpp"

namespace felide {
    Component::Component(MessageBus *messageBus) {
        this->messageBus = messageBus;
    }

    Component::~Component() {}

    MessageBus* Component::getBus() const {
        return this->messageBus;
    }
}
