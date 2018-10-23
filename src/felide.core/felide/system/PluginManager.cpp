
#include "PluginManager.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <boost/dll.hpp>
#include <boost/filesystem/path.hpp>
#include <felide/util/OS.hpp>
#include "Plugin.hpp"

namespace felide {
    typedef felide::Plugin* (*PluginCreateProc)();
    typedef void (*PluginDestroyProc)(Plugin *plugin);

    class PluginProxy : public Plugin {
    public:
        explicit PluginProxy(const boost::filesystem::path &libraryPath) {
            const auto loadMode = boost::dll::load_mode::default_mode;

            m_library = boost::dll::shared_library(libraryPath, loadMode);
            m_pluginCreate = m_library.get<Plugin*()>("felide_plugin_create");
            m_pluginDestroy = m_library.get<void (Plugin*)>("felide_plugin_destroy");

            m_plugin = m_pluginCreate();
        }

        virtual ~PluginProxy() {
            if (m_pluginDestroy && m_plugin) {
                m_pluginDestroy(m_plugin);
            }
        }

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
        PluginCreateProc m_pluginCreate = nullptr;
        PluginDestroyProc m_pluginDestroy = nullptr;
        Plugin *m_plugin = nullptr;
        boost::dll::shared_library m_library;
    };

    struct PluginManager::Private {
        Core *core = nullptr;
        std::vector<std::unique_ptr<Plugin>> plugins;
        std::vector<std::string> searchPaths;
    };

    PluginManager::PluginManager(Core *core) {
        assert(core);
        m_impl = new PluginManager::Private();
        m_impl->core = core;

        // TODO: Export this to a configuration file
        m_impl->searchPaths = {
            "/usr/local/lib",
            "build/Debug/"
        };
    }

    PluginManager::~PluginManager() {
        delete m_impl;
    }

    std::string mapNameToNative(const std::string &name) {
        switch (getCurrentOS()) {
            case OS::Windows: return name + ".dll";
            case OS::Linux : return "lib" + name + ".so";
            default: return name;
        }
    }
    
    void PluginManager::loadPlugin(const std::string &name) {

        for (const std::string &searchPath : m_impl->searchPaths) {
            const boost::filesystem::path path = searchPath;

            if (!boost::filesystem::exists(path)) {
                continue;
            }

            try {
                std::cout << "Loading " << name << std::endl;
                const auto mappedName = mapNameToNative(name);
                auto plugin = new PluginProxy(path / mappedName);

                m_impl->plugins.emplace_back(plugin);

                plugin->start(m_impl->core);

                std::cout << "Load OK " << name << std::endl;
                break;
            } catch (const std::exception &exp) {
                const std::string msg = exp.what();
                std::cout << "Load failed:" << std::endl << msg << std::endl;
            }

            std::cout << "Load OK " << name << std::endl;
        }
    }
}
