
#ifndef __FELIDE_SYSTEM_PLUGINQT_HPP__
#define __FELIDE_SYSTEM_PLUGINQT_HPP__

#include <felide/system/Plugin.hpp>
#include "../ui/qt5/ViewFactoryQt.hpp"

namespace felide {
    class PluginQt : public Plugin {
    public:
        PluginQt();

        virtual ~PluginQt();

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

        virtual PluginInformation getInformation() const override;

    private:
        ViewFactoryQt m_viewFactory;
    };
}

#endif