
#ifndef __FELIDE_SYSTEM_PLUGINMANAGER_HPP__
#define __FELIDE_SYSTEM_PLUGINMANAGER_HPP__

#include <string>

namespace felide {
    class Plugin;
    class Core;

    class PluginManager {
    public:
        explicit PluginManager(Core *core);

        ~PluginManager();

        void loadPlugin(const std::string &name);

    private:
        Core *m_core = nullptr;
    };
} 

#endif
