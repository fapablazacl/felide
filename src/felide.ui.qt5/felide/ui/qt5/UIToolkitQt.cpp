
#include "UIToolkitQt.hpp"

#include <QApplication>
#include "IDEFrameQt.hpp"
#include <felide/ui/IDEFramePresenter.hpp>

#include <boost/filesystem.hpp>

namespace felide {
    int UIToolkitQt::runApp(int argc, char **argv) {
        QApplication app(argc, argv);

        IDEFramePresenter presenter;

        IDEFrameQt ideFrame(&presenter);
        ideFrame.show();

        if (argc > 1) {
            // TODO: Add command line parsing support
            const auto fullPath = boost::filesystem::current_path() / argv[1];
            presenter.openFolder(fullPath.string());
        }

        return app.exec();
    }
}
