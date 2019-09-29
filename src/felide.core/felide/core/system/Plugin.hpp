
#ifndef __FELIDE_SYSTEM_PLUGIN_HPP__
#define __FELIDE_SYSTEM_PLUGIN_HPP__

#include <string>
#include "../Version.hpp"

namespace felide {
    struct PluginInformation {
        std::string name;
        std::string description;
        Version version;
    };

    class FELIDE_API Core;
    class FELIDE_API Plugin {
    public:
        virtual ~Plugin();

        virtual void start(Core *core) = 0;

        virtual void stop(Core *core) = 0;

        virtual PluginInformation getInformation() const = 0;
    };
}

#endif
