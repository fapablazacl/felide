
#include "UIToolkitQt.hpp"

#include <QApplication>
#include "IDEFrameQt.hpp"

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv, IDEFramePresenter *presenter) {
        QApplication app(argc, argv);

        IDEFrameQt ideFrame(presenter);
        ideFrame.show();

        return app.exec();
    }
}
