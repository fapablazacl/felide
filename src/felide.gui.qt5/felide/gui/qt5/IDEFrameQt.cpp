
#include "IDEFrameQt.hpp"

#include <vector>
#include <functional>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <iostream>
#include <felide/gui/ide-frame/IDEFramePresenter.hpp>

#include "DocumentQt.hpp"
#include "DialogManagerQt.hpp"
#include "FolderBrowserQt.hpp"
#include "UtilitiesQt.hpp"


namespace felide {
    IDEFrameQt::IDEFrameQt(IDEFramePresenter *presenter) : IDEFrame(presenter) {
        m_dialogManager = std::make_unique<DialogManagerQt>(this);

        this->setupDocumentManager();
        this->setupDockUI();

        QDesktopWidget desktopWidget;
        
        const QRect screenSize = desktopWidget.availableGeometry(desktopWidget.primaryScreen());
        
        this->setMinimumSize(screenSize.size() * 0.4);
        this->resize(screenSize.size() * 0.7);

        m_presenter->onInitialized(this, m_dialogManager.get(), this);
    }

    void IDEFrameQt::setupMenuBar(const Menu &menu) {
        this->setMenuBar(createMenuBar(this, menu));
    }

    void IDEFrameQt::setupDocumentManager() {
        // documentManager = new QMdiDocumentManager(this, m_presenter->getDocumentManagerPresenter());
        this->setCentralWidget(documentManager);
    }
    
    void IDEFrameQt::setupDockUI() {
        const auto areas = QFlags<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        
        // setup folder browser dock widget
        m_folderBrowserDock = new QDockWidget("Folder Browser", this);
        
        m_folderBrowser = new FolderBrowserQt(m_folderBrowserDock, m_presenter->getFolderBrowserPresenter(), m_dialogManager.get());
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
        return documentManager;
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
