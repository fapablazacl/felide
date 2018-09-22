
#include "ViewFactoryQt.hpp"

namespace felide {
    int ViewFactoryQt::runApp(int argc, char **argv) {
        QApplication app(argc, argv);

        MainWindow mainWindow;
        mainWindow.show();

        return app.exec();
    }
}
