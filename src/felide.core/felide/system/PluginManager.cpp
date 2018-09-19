
#include "PluginManager.hpp"

#include <stdexcept>
#include <iostream>
#include <boost/dll.hpp>

namespace felide {


    PluginManager::PluginManager(Core *core) {
        m_core = core;
    }

    PluginManager::~PluginManager() {}

    void PluginManager::loadPlugin(const std::string &name) {
        // TODO: Export this to a configuration file
        const std::string pluginPath = "/usr/local/lib/";

        typedef felide::Plugin* (*PluginCreateProc);

        try {
            std::cout << "Loading " << name << std::endl;

            auto felide_plugin_create = boost::dll::import<PluginCreateProc> (
                pluginPath + name,
                "felide_plugin_create",
                boost::dll::load_mode::append_decorations
            );

            if (!felide_plugin_create) {
                throw std::runtime_error("Required entry point doesn't exist.");
            }

            std::cout << "Load OK " << name << std::endl;
        } catch (const std::exception &exp) {
            std::cout << "Load failed:" << std::endl << exp.what() << std::endl;
        }
    }
}
