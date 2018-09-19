
#include "Core.hpp"

#include <felide/system/PluginManager.hpp>

namespace felide {
    Core::Core() {
        m_pluginManager = new PluginManager(this);
        // m_UIManager = new UIManager();
    }

    Core::~Core() {
        if (m_pluginManager) {
            delete m_pluginManager;
        }

        if (m_UIManager) {
            delete m_UIManager;
        }
    }

    PluginManager* Core::getPluginManager() {
        return m_pluginManager;
    }

    UIManager* Core::getUIManager() {
        return m_UIManager;
    }
} 
