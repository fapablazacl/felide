
#include "PluginManager.hpp"

#include <stdexcept>
#include <iostream>
#include <boost/dll.hpp>
#include "Plugin.hpp"

namespace felide {
    typedef felide::Plugin* (*PluginCreateProc)();

    class PluginProxy : public Plugin {
    public:
        explicit PluginProxy(const std::string &libraryPath) {
            m_library = boost::dll::shared_library(libraryPath, boost::dll::load_mode::append_decorations);

            auto pluginCreate = m_library.get<Plugin*()>("felide_plugin_create");
            m_plugin = pluginCreate();
        }

        virtual ~PluginProxy() {}

        virtual void start(Core *core) override {
            return m_plugin->start(core);
        }

        virtual void stop(Core *core) override {
            return m_plugin->stop(core);
        }

        virtual PluginInformation getInformation() const override {
            return m_plugin->getInformation();
        }

    private:
        PluginCreateProc m_pluginCreateProc = nullptr;
        Plugin *m_plugin = nullptr;
        boost::dll::shared_library m_library;
    };

    PluginManager::PluginManager(Core *core) {
        m_core = core;
    }

    PluginManager::~PluginManager() {}
    
    void PluginManager::loadPlugin(const std::string &name) {
        // TODO: Export this to a configuration file
        const std::string pluginFolder = "/usr/local/lib/";

        try {
            std::cout << "Loading " << name << std::endl;
            auto plugin = new PluginProxy(pluginFolder + name);

            m_plugins.emplace_back(plugin);

            std::cout << "Load OK " << name << std::endl;
        } catch (const std::exception &exp) {
            std::cout << "Load failed:" << std::endl << exp.what() << std::endl;
        }
    }
}
