
#include <cassert>
#include <felide/Core.hpp>
#include <felide/ui/ViewFactory.hpp>
#include <felide/system/PluginManager.hpp>

#include <iostream>

int main(int argc, char **argv) {
    felide::Core core;

    auto pluginManager = core.getPluginManager();
    pluginManager->loadPlugin("felide.ui.qt5");

    auto viewFactory = core.getViewFactory();
    assert(viewFactory);

    auto mainWindow = viewFactory->createMainWindow();

    return 0;
}

/*
#include <QApplication>
#include "felide/ui/qt5/MainWindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    felide::MainWindow window;

    window.show();

    return app.exec();
}
*/
