
#include <QApplication>

#include "felide/gui/mvp/MainFrame.hpp"
#include "QMainFrame.hpp"


class MainFrameModel : public felide::MainFrame::Model {
public:
    std::string getTitle() const override {
        return "test-";
    }

    bool hasModifiedFiles() const override {
        return true;

    }
};


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    using namespace felide;

    MainFrameModel model{};
    MainFrame::Presenter presenter{&model};
    QMainFrame view{&presenter};

    view.show();

    return app.exec();
}
