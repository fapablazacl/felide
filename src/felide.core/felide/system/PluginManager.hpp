
#ifndef __FELIDE_SYSTEM_PLUGINMANAGER_HPP__
#define __FELIDE_SYSTEM_PLUGINMANAGER_HPP__

namespace felide {
    class Plugin;
    class Core;

    class PluginManager {
    public:
        explicit PluginManager(Core *core);

        ~PluginManager();

    private:
        Core *m_core = nullptr;
    };
} 

#endif
