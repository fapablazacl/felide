
#include <QApplication>

#include "felide/ui/qt5/MainWindow/MainWindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    felide::MainWindow window;

    window.show();

    return app.exec();
}
