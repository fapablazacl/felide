
#include "PluginQt.hpp"

#include <felide/Core.hpp>

namespace felide {
    PluginQt::PluginQt() {}

    PluginQt::~PluginQt() {}

    void PluginQt::start(Core *core) {

    }

    void PluginQt::stop(Core *core) {

    }

    PluginInformation PluginQt::getInformation() const {
        return {"", "", {0, 0, 0, 0}};
    }
}

extern "C" felide::Plugin* felide_plugin_create() {
    return new felide::PluginQt();
}
