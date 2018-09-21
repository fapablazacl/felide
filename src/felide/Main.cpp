
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
    pluginManager->loadPlugin("felide.ui.qt5");

    auto viewFactory = core.getViewFactory();
    assert(viewFactory);

    auto mainLoop = viewFactory->createMainLoop(argc, argv);

    auto mainWindow = viewFactory->createMainWindow();

    return mainLoop->run();
}
