
#include <QApplication>

#include <felide/gui/mvp/MainFrame.hpp>
#include <felide/gui/qt5/QMainFrame.hpp>

using felide::MainFrame;
using felide::QMainFrame;

class MainFrameModelMock : public MainFrame::Model {
public:
    std::string getTitle() const override {
        return "XenoIde";
    }

    bool hasModifiedFiles() const override {
        return true;
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainFrameModelMock model;
    MainFrame::Presenter presenter{&model};
    QMainFrame view{&presenter};

    return app.exec();
}


/*
#include <felide/gui/qt5/IDEFrameQt.hpp>
#include <felide/gui/ide-frame/IDEFrameModel.hpp>
#include <felide/gui/ide-frame/IDEFramePresenter.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char **argv) {
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
*/