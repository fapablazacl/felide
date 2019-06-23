
#include <QApplication>

#include <felide/ui/qt5/IDEFrameQt.hpp>
#include <felide/ui/ide-frame/IDEFrameModel.hpp>
#include <felide/ui/ide-frame/IDEFramePresenter.hpp>
#include <boost/filesystem.hpp>

int felide_main(int argc, char **argv) {
    using namespace felide;

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
