
#include "UIToolkitQt.hpp"

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv) {
        QApplication app(argc, argv);

        MainWindow mainWindow;
        mainWindow.show();

        return app.exec();
    }
}
