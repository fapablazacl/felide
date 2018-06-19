
#include <QApplication>
#include <Felide/MainWindow.hpp>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    felide::MainWindow window;

    window.show();

    return app.exec();
}
