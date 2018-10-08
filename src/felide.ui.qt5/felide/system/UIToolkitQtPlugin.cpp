
#include "UIToolkitQtPlugin.hpp"

#include <felide/Core.hpp>

namespace felide {
    UIToolkitQtPlugin::UIToolkitQtPlugin() {}

    UIToolkitQtPlugin::~UIToolkitQtPlugin() {}

    void UIToolkitQtPlugin::start(Core *core) {
        core->setToolkit(&m_toolkit);
    }

    void UIToolkitQtPlugin::stop(Core *core) {
        core->setToolkit(nullptr);
    }

    PluginInformation UIToolkitQtPlugin::getInformation() const {
        return {"felide.ui.qt5", "Qt5 User Interface Plugin", Version{0, 0, 1}};
    }
}

extern "C" felide::Plugin* felide_plugin_create() {
    return new felide::UIToolkitQtPlugin();
}

extern "C" void felide_plugin_destroy(felide::Plugin *plugin) {
    delete plugin;
}
