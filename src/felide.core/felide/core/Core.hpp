
#ifndef __FELIDE_CORE_HPP__
#define __FELIDE_CORE_HPP__

#include "Predef.hpp"

namespace felide {
    class FELIDE_API PluginManager;
    class FELIDE_API UIToolkit;

    class FELIDE_API Core {
    public:
        Core();
        ~Core();

        PluginManager* getPluginManager();

        UIToolkit* getToolkit();

        void setToolkit(UIToolkit* toolkit);

    private:
        PluginManager *m_pluginManager = nullptr;
        UIToolkit *m_toolkit = nullptr;
    };
} 

#endif
