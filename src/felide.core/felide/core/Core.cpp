
#include "Core.hpp"

#include <iostream>
#include <felide/core/system/PluginManager.hpp>

namespace felide {
    Core::Core() {
        m_pluginManager = new PluginManager(this);
    }

    Core::~Core() {
        if (m_pluginManager) {
            delete m_pluginManager;
        }
    }

    PluginManager* Core::getPluginManager() {
        return m_pluginManager;
    }

    UIToolkit* Core::getToolkit() {
        return m_toolkit;
    }

    void Core::setToolkit(UIToolkit* toolkit) {
        if (m_toolkit) {
            std::cout << "felide::Core::setToolkit: Already setted view factory!!" << std::endl;
        }

        m_toolkit = toolkit;
    }
}
