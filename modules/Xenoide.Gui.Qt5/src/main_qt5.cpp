
#include <QApplication>

#include <Xenoide/GUI/Qt5/IDEFrameQt.hpp>
#include <Xenoide/GUI/IDEFrameModel.hpp>
#include <Xenoide/GUI/IDEFramePresenter.hpp>
#include <boost/filesystem.hpp>

int felide_main_qt5(int argc, char **argv) {
    using namespace Xenoide;

    QApplication app(argc, argv);

    auto model = IDEFrameModel::create();
    auto presenter = IDEFramePresenter{model.get()};
    auto view = IDEFrameQt{&presenter};

    view.show();

    // TODO: Add command line parsing
    if (argc > 1) {
        const auto fullPath = boost::filesystem::current_path() / argv[1];
        presenter.openFolder(fullPath.string());
    }

    return app.exec();
}
