
#ifndef __FELIDE_SYSTEM_PLUGINMANAGER_HPP__
#define __FELIDE_SYSTEM_PLUGINMANAGER_HPP__

#include <string>
#include <vector>
#include <memory>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API Plugin;
    class FELIDE_API Core;

    class FELIDE_API PluginManager {
    public:
        explicit PluginManager(Core *core);

        ~PluginManager();

        void loadPlugin(const std::string &name);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
