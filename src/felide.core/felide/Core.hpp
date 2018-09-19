
#ifndef __FELIDE_CORE_HPP__
#define __FELIDE_CORE_HPP__

namespace felide {
    class PluginManager;
    class ViewFactory;

    class Core {
    public:
        Core();
        ~Core();

        PluginManager* getPluginManager();

        ViewFactory* getViewFactory();

        void setViewFactory(ViewFactory* factory);

    private:
        PluginManager *m_pluginManager = nullptr;
        ViewFactory *m_viewFactory = nullptr;
    };
} 

#endif
