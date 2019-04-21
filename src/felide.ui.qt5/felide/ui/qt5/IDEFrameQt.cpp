
#include "IDEFrameQt.hpp"

#include <vector>
#include <functional>
#include <QMessageBox>
#include <QDesktopWidget>
#include <iostream>
#include <felide/ui/ide-frame/IDEFramePresenter.hpp>

#include "EditorQt.hpp"
#include "DialogManagerQt.hpp"
#include "FolderBrowserQt.hpp"
#include "UtilitiesQt.hpp"

namespace felide {
    IDEFrameQt::IDEFrameQt(IDEFramePresenter *presenter) : IDEFrame(presenter), m_editorManagerPresenter(nullptr), m_folderBrowserPresenter(presenter) {
        m_dialogManager = std::make_unique<DialogManagerQt>(this);

        this->setupMenuBar();
        this->setupEditorManager();
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

    void IDEFrameQt::setupEditorManager() {
        m_editorManager = new EditorManagerQt(this, &m_editorManagerPresenter);

        connect(m_editorManager, &EditorManagerQt::editorContentChanged, [&](EditorQt *editor) {
            assert(editor);
            m_presenter->onEditorContentModified(editor);
        });
        
        connect(m_editorManager, &EditorManagerQt::editorCloseRequested, [&](EditorQt *editor) {
            assert(editor);
            m_presenter->onEditorCloseRequested(editor);
        });

        this->setCentralWidget(m_editorManager);
    }
    
    void IDEFrameQt::setupDockUI() {
        const auto areas = QFlags<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        
        // setup folder browser dock widget
        m_folderBrowserDock = new QDockWidget("Folder Browser", this);
        
        m_folderBrowser = new FolderBrowserQt(m_folderBrowserDock, &m_folderBrowserPresenter, m_dialogManager.get());
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
    EditorManager* IDEFrameQt::getEditorManager() {
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
}
