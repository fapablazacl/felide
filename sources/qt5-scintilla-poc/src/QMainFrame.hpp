
#pragma once 

#include <QMainWindow>
#include <QDockWidget>
#include <QTextEdit>
#include <QTreeView>
#include <felide/gui/mvp/MainFrame.hpp>

namespace felide {
    class QMainFrame : public QMainWindow, public MainFrame::View {
        Q_OBJECT

    public:
        explicit QMainFrame(MainFrame::Presenter *presenter);
        
        virtual ~QMainFrame();

        void displayTitle(const std::string &value) override;

        void changeWindowState(const MainFrame::Window window, const MainFrame::VisibleState state) override;

        void show() override;

        MainFrame::AskResult askCloseConfirmation(const std::string &title, const std::string &prompt) override;

    private:
        void closeEvent(QCloseEvent *event) override;

        QSize computeFrameSize() const;

    private:
        QDockWidget *outputWindowDockWidget = nullptr;
        QTextEdit *outputWindowTextEdit = nullptr;

        QDockWidget *folderBrowserDockWidget = nullptr;
        QTreeView *folderBrowserTreeView = nullptr;
    };
}
