
#include "QMainFrame.hpp"

#include <QDesktopWidget>
#include <QCloseEvent>
#include <QMessageBox>


namespace felide {
    QMainFrame::QMainFrame(MainFrame::Presenter *presenter) : MainFrame::View(presenter) {
        this->setMinimumSize(this->computeFrameSize());

        outputWindowDockWidget = new QDockWidget("Output Window", this);
        outputWindowTextEdit = new QTextEdit(this);
        outputWindowDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
        outputWindowDockWidget->setWidget(outputWindowTextEdit);
        this->addDockWidget(Qt::BottomDockWidgetArea, outputWindowDockWidget);
        
        folderBrowserDockWidget = new QDockWidget("Folder Browser", this);
        folderBrowserTreeView = new QTreeView(this);
        folderBrowserDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
        folderBrowserDockWidget->setWidget(folderBrowserTreeView);
        this->addDockWidget(Qt::LeftDockWidgetArea, folderBrowserDockWidget);

        this->setCentralWidget(createCodeEditor());

        presenter->handleInitializedView(this);
    }

    QMainFrame::~QMainFrame() {}

    QsciScintilla* QMainFrame::createCodeEditor() {
        QsciScintilla* scintilla = new QsciScintilla(this);

        scintilla->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, false);
        scintilla->setMarginWidth(1, QString("1000"));

        auto font = QFont{"Inconsolata", 12};

        scintilla->setFont(font);
        scintilla->setCaretLineVisible(true);
        scintilla->setTabWidth(4);
        scintilla->setMarginType(1, QsciScintilla::NumberMargin);

        return scintilla;
    }

    void QMainFrame::displayTitle(const std::string &value) {
        this->setWindowTitle(value.c_str());
    }

    void QMainFrame::changeWindowState(const MainFrame::Window window, const MainFrame::VisibleState state) {
        const bool visible = (state == MainFrame::VS_SHOW);
        
        switch (window) {
        case MainFrame::W_OUTPUT:
            outputWindowDockWidget->setVisible(visible);
            break;

        case MainFrame::W_FOLDERBROWSER:
            folderBrowserDockWidget->setVisible(visible);
            break;
        }
    }

    void QMainFrame::show() {
        assert(presenter);

        QMainWindow::show();
    }

    MainFrame::AskResult QMainFrame::askCloseConfirmation(const std::string &title, const std::string &prompt) {
        assert(presenter);

        const auto button = QMessageBox::Yes | QMessageBox::No;
        const int result = QMessageBox::question(this, title.c_str(), prompt.c_str(), button);

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
