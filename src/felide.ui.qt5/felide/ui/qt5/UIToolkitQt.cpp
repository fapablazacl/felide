
#include "UIToolkitQt.hpp"

#include <QApplication>
#include "MainWindowQt.hpp"

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv, MainWindowPresenter *presenter) {
        QApplication app(argc, argv);

        MainWindowQt mainWindow(presenter);
        mainWindow.show();

        return app.exec();
    }
}
