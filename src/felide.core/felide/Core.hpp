
#ifndef __FELIDE_CORE_HPP__
#define __FELIDE_CORE_HPP__

#include "Predef.hpp"

namespace felide {
    class FELIDE_API PluginManager;
    class FELIDE_API ViewFactory;

    class FELIDE_API Core {
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
