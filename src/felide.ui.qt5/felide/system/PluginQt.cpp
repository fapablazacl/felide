
#include "PluginQt.hpp"

#include <felide/Core.hpp>

namespace felide {
    PluginQt::PluginQt() {}

    PluginQt::~PluginQt() {}

    void PluginQt::start(Core *core) {
        core->setViewFactory(&m_viewFactory);
    }

    void PluginQt::stop(Core *core) {
        core->setViewFactory(nullptr);
    }

    PluginInformation PluginQt::getInformation() const {
        return {"felide.ui.qt5", "Qt5 User Interface Plugin", Version{0, 0, 1}};
    }
}

extern "C" felide::Plugin* felide_plugin_create() {
    return new felide::PluginQt();
}
