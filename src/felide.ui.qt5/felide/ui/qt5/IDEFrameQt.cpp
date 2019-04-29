
#include "IDEFrameQt.hpp"

#include <vector>
#include <functional>
#include <QMessageBox>
#include <QDesktopWidget>
#include <iostream>
#include <felide/ui/ide-frame/IDEFrameController.hpp>

#include "DocumentQt.hpp"
#include "DialogManagerQt.hpp"
#include "FolderBrowserQt.hpp"
#include "UtilitiesQt.hpp"

namespace felide {
    IDEFrameQt::IDEFrameQt(IDEFrameController *presenter) : IDEFrame(presenter), m_editorManagerController(nullptr), m_folderBrowserController(presenter) {
        m_dialogManager = std::make_unique<DialogManagerQt>(this);

        this->setupMenuBar();
        this->setupDocumentManager();
        this->setupDockUI();

        QDesktopWidget desktopWidget;
        
        const QRect screenSize = desktopWidget.availableGeometry(desktopWidget.primaryScreen());
        
        this->setMinimumSize(screenSize.size() * 0.4);
        this->resize(screenSize.size() * 0.7);

        m_presenter->attachView(this);
    }

    void IDEFrameQt::setupMenuBar() {
        this->setMenuBar(createMenuBar(this, *m_menu));
    }

    void IDEFrameQt::setupDocumentManager() {
        m_editorManager = new DocumentManagerQt(this, &m_editorManagerController);

        connect(m_editorManager, &DocumentManagerQt::editorContentChanged, [&](DocumentQt *editor) {
            assert(editor);
            m_presenter->onDocumentContentModified(editor);
        });
        
        connect(m_editorManager, &DocumentManagerQt::editorCloseRequested, [&](DocumentQt *editor) {
            assert(editor);
            m_presenter->onDocumentCloseRequested(editor);
        });

        this->setCentralWidget(m_editorManager);
    }
    
    void IDEFrameQt::setupDockUI() {
        const auto areas = QFlags<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        
        // setup folder browser dock widget
        m_folderBrowserDock = new QDockWidget("Folder Browser", this);
        
        m_folderBrowser = new FolderBrowserQt(m_folderBrowserDock, &m_folderBrowserController, m_dialogManager.get());
        m_folderBrowserDock->setAllowedAreas(areas);
        m_folderBrowserDock->setWidget(m_folderBrowser);

        this->addDockWidget(Qt::LeftDockWidgetArea, m_folderBrowserDock);
    }
    
    void IDEFrameQt::closeEvent(QCloseEvent *evt) {
        if (m_presenter->onCloseRequested()) {
            evt->accept();
        } else {
            evt->ignore();
        }
    }
}

namespace felide {
    DocumentManager* IDEFrameQt::getDocumentManager() {
        return m_editorManager;
    }

    DialogManager* IDEFrameQt::getDialogManager() {
        return m_dialogManager.get();
    }
    
    FolderBrowser* IDEFrameQt::getFolderBrowser() {
        return m_folderBrowser;
    }
    
    void IDEFrameQt::close() {
        QMainWindow::close();
    }

    void IDEFrameQt::show() {
        QMainWindow::show();
    }

    static FileDialogData mapFileOperationVD(const IDEFrame::FileOperationViewData &viewData, const FileDialogType type) {
        auto fileDialogData = FileDialogData();

        if (viewData.defaultFilePath) {
            fileDialogData.defaultPath = viewData.defaultFilePath.get().string();
        }

        fileDialogData.filters = viewData.filters;
        fileDialogData.title = viewData.title;
        fileDialogData.type = type;

        return fileDialogData;
    }
    
    boost::optional<boost::filesystem::path> IDEFrameQt::showFileOpenDialog(const FileOperationViewData &viewData) const {
        const FileDialogData fileDialogData = mapFileOperationVD(viewData, FileDialogType::OpenFile);

        if (auto result = m_dialogManager->showFileDialog(fileDialogData); result) {
            return boost::filesystem::path(result.get());
        }

        return {};
    }

    boost::optional<boost::filesystem::path> IDEFrameQt::showFileSaveDialog(const FileOperationViewData &viewData) const {
        const FileDialogData fileDialogData = mapFileOperationVD(viewData, FileDialogType::SaveFile);

        if (auto result = m_dialogManager->showFileDialog(fileDialogData); result) {
            return boost::filesystem::path(result.get());
        }

        return {};
    }

    boost::optional<boost::filesystem::path> IDEFrameQt::showFolderOpenDialog(const IDEFrame::FolderOpenViewData &viewData) const {
        const std::string &title = viewData.title;

        if (auto result = m_dialogManager->showFolderDialog(title); result) {
            return boost::filesystem::path(result.get());
        }

        return {};
    }
}
