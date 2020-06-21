
#include "QMainFrame.hpp"

#include <QDesktopWidget>
#include <QCloseEvent>
#include <QMessageBox>

namespace felide {
    QMainFrame::QMainFrame(MainFrame::Presenter *presenter) : MainFrame::View(presenter) {
        this->setMinimumSize(this->computeFrameSize());

        presenter->handleInitializedView(this);
    }

    QMainFrame::~QMainFrame() {}

    void QMainFrame::changeTitle(const std::string &value) {
        this->setWindowTitle(value.c_str());
    }

    void QMainFrame::changeWindowState(const MainFrame::Window window, const MainFrame::VisibleState state) {

    }

    void QMainFrame::show() {
        QMainWindow::show();
    }

    MainFrame::AskResult QMainFrame::askCloseConfirmation(const std::string &title, const std::string &prompt) {
        const int result = QMessageBox::question(this, title.c_str(), prompt.c_str(), QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::Yes) {
            return MainFrame::AR_OK;
        }

        return MainFrame::AR_CANCEL;
    }
}

namespace felide {
    void QMainFrame::closeEvent(QCloseEvent *event) {
        assert(presenter);

        if (presenter->handleCloseRequest() == MainFrame::CRA_CLOSE) {
            event->accept();
        } else {
            event->ignore();
        }
    }

    QSize QMainFrame::computeFrameSize() const {
        const double factor = 0.4;
        const QDesktopWidget desktopWidget;
        const QRect screenSize = desktopWidget.availableGeometry(desktopWidget.primaryScreen());

        return screenSize.size() * factor;
    }
}
