
#ifndef __FELIDE_UI_QT5_VIEWFACTORYQT5_HPP__
#define __FELIDE_UI_QT5_VIEWFACTORYQT5_HPP__

#include <felide/ui/ViewFactory.hpp>

#include "MainWindow.hpp"
#include "MainLoopImpl.hpp"

namespace felide {
    class ViewFactoryQt : public ViewFactoryImpl<MainWindow, MainLoopImpl> {
    public:
        virtual int runApp(int argc, char **argv) override;
    };
}

#endif
