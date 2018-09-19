
#include "Core.hpp"

#include <iostream>
#include <felide/system/PluginManager.hpp>

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

    ViewFactory* Core::getViewFactory() {
        return m_viewFactory;
    }

    void Core::setViewFactory(ViewFactory* factory) {
        if (m_viewFactory) {
            std::cout << "felide::Core::setViewFactory: Already setted view factory!!" << std::endl;
        }

        m_viewFactory = factory;
    }
}
