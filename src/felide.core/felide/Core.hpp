
#ifndef __FELIDE_CORE_HPP__
#define __FELIDE_CORE_HPP__

namespace felide {
    class PluginManager;
    class UIManager;

    class Core {
    public:
        Core();
        ~Core();

        PluginManager* getPluginManager();

        UIManager* getUIManager();

    private:
        PluginManager *m_pluginManager = nullptr;
        UIManager *m_UIManager = nullptr;
    };
} 

#endif
