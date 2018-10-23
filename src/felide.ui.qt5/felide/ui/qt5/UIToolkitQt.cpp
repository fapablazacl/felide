
#include "UIToolkitQt.hpp"

#include <QApplication>
#include "IDEFrameQt.hpp"
#include <felide/ui/IDEFramePresenter.hpp>

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv) {
        QApplication app(argc, argv);

        IDEFramePresenter presenter;

        IDEFrameQt ideFrame(&presenter);
        ideFrame.show();

        return app.exec();
    }
}
