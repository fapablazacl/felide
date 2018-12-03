/*
#ifndef __FELIDE_SYSTEM_PLUGINQT_HPP__
#define __FELIDE_SYSTEM_PLUGINQT_HPP__

#include <felide/system/Plugin.hpp>
#include "../ui/qt5/UIToolkitQt.hpp"

namespace felide {
    class UIToolkitQtPlugin : public Plugin {
    public:
        UIToolkitQtPlugin();

        virtual ~UIToolkitQtPlugin();

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

        virtual PluginInformation getInformation() const override;

    private:
        UIToolkitQt m_toolkit;
    };
}

#endif
*/
