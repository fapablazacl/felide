
#include "PluginManager.hpp"

#include <exception>
#include <iostream>
#include <boost/dll.hpp>

namespace felide {
    PluginManager::PluginManager(Core *core) {
        m_core = core;
    }

    PluginManager::~PluginManager() {}

    void PluginManager::loadPlugin(const std::string &name) {
        typedef felide::Plugin* (*PluginCreateProc);

        try {
            std::cout << "Loading " << name << std::endl;

            auto felide_plugin_create = boost::dll::import<PluginCreateProc> (
                name,                     
                "felide_plugin_create", 
                boost::dll::load_mode::append_decorations
            );

            std::cout << "Load OK " << name << std::endl;
        } catch (const std::exception &exp) {
            std::cout << exp.what() << std::endl;
        }
    }
}
