
#include "UIToolkitQt.hpp"

#include <QApplication>
#include "MainWindow.hpp"

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv, MainWindowPresenter *presenter) {
        QApplication app(argc, argv);

        MainWindow mainWindow(presenter);
        mainWindow.show();

        return app.exec();
    }
}
