
#include <cassert>
#include <felide/Core.hpp>
#include <felide/ui/ViewFactory.hpp>
#include <felide/ui/MainWindowView.hpp>
#include <felide/ui/MainLoop.hpp>
#include <felide/system/PluginManager.hpp>

#include <iostream>

int main(int argc, char **argv) {
    felide::Core core;

    auto pluginManager = core.getPluginManager();
    pluginManager->loadPlugin("libfelide.ui.qt5.so");

    auto viewFactory = core.getViewFactory();
    assert(viewFactory);

    auto mainLoop = viewFactory->createMainLoop(argc, argv);
    assert(mainLoop);

    auto mainWindow = viewFactory->createMainWindow();
    assert(mainWindow);

    /*
    mainWindow->show();
    */

    return mainLoop->run();
}
