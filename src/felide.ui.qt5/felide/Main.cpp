
#include <QApplication>

#include <felide/ui/qt5/IDEFrameQt.hpp>
#include <felide/ui/IDEFramePresenter.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char **argv) {
    using namespace felide;

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
