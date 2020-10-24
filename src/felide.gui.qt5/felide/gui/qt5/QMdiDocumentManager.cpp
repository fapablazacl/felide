
#include "QMdiDocumentManager.hpp"

#include <iostream>
#include <QGridLayout>
#include <QAction>
#include <QMenu>
#include <QMdiSubWindow>

#include <felide/gui/document/DocumentPresenter.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>

#include "DocumentQt.hpp"
#include "QMdiSubWindowDocument.hpp"

namespace felide {
    QMdiDocumentManager::QMdiDocumentManager(QWidget *parent, DocumentManagerPresenter *presenter) : QWidget(parent), DocumentManager(presenter), dialogManager(this) {
        mMdiArea = new QMdiArea(this);
        mMdiArea->setViewMode(QMdiArea::TabbedView);
        mMdiArea->setTabsClosable(true);
        mMdiArea->setTabsMovable(true);
        // mMdiArea->setDocumentMode(true);

        mMdiArea->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(mMdiArea, &QMdiArea::customContextMenuRequested, [this](const QPoint &pos) {
            std::cout << "asdasdasd" << std::endl;
            bool found = true;
            int index = 0;

            // determine the tab
            auto list = mMdiArea->subWindowList();

            /*
            for (int i=0; i<list.count(); i++) {
                const auto rect = m_tabWidget->tabBar()->tabRect(i);

                if (rect.contains(pos)) {
                    found = true;
                    index = i;
                    break;
                }
            }
            */

            // TODO: Generate menu Dnamically
            // trigger context menu on that tab
            if (found) {
                Document *editor = this->getDocument(index);
                QMenu contextMenu("Context Menu", this);

                QAction closeAction("Close", this);
                contextMenu.addAction(&closeAction);
                this->connect(&closeAction, &QAction::triggered, [this, editor]() {
                    this->presenter->onCloseDocument(editor);
                });

                QAction closeAllButThisAction("Close all but this", this);
                contextMenu.addAction(&closeAllButThisAction);
                this->connect(&closeAllButThisAction, &QAction::triggered, [this, editor]() {
                    this->presenter->onCloseOtherDocuments(editor);
                });

                QAction closeAllAction("Close all", this);
                contextMenu.addAction(&closeAllAction);
                this->connect(&closeAllAction, &QAction::triggered, [this]() {
                    this->presenter->onCloseAllDocuments();
                });

                QAction closeToTheRightAction("Close to the right", this);
                contextMenu.addAction(&closeToTheRightAction);
                this->connect(&closeToTheRightAction, &QAction::triggered, [this, editor]() {
                    this->presenter->onCloseDocumentsToTheRight(editor);
                });

                contextMenu.exec(this->mapToGlobal(pos));
            }
        });

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(mMdiArea);
        this->setLayout(layout);

        presenter->onInitialized(this, &dialogManager);
    }

    QMdiDocumentManager::~QMdiDocumentManager() {}
    
    boost::optional<int> QMdiDocumentManager::getDocumentIndex(const DocumentQt *document) {
        assert(mMdiArea);
        assert(document);

        auto list = mMdiArea->subWindowList();

        for (int i = 0; i < list.count(); i++) {
            const QMdiSubWindow *subWindow = list[i];

            if (subWindow->widget() == document) {
                return i;
            }
        }

        return {};
    }
    
    void QMdiDocumentManager::changeDocumentTitle(DocumentQt *document, const std::string &title) {
        assert(document);

        auto subWindowIt = documentSubWindowMap.find(document);
        assert(subWindowIt != documentSubWindowMap.end());

        subWindowIt->second->setWindowTitle(title.c_str());
    }
}

namespace felide {
    Document* QMdiDocumentManager::appendDocument(DocumentPresenter *documentPresenter) {
        assert(mMdiArea);
        assert(documentPresenter);

        auto subWindow = new QMdiSubWindowDocument();
        auto document = new DocumentQt(subWindow, documentPresenter);

        subWindow->setWidget(document);
        subWindow->setAttribute(Qt::WA_DeleteOnClose, true); // Prevents memory leak

        mMdiArea->addSubWindow(subWindow);

        documentSubWindowMap.insert({document, subWindow});

        /*
        connect(mdiArea, &QMdiArea::tabCloseRequested, [=] (int tabIndex) {
            QWidget *widget = m_tabWidget->widget(tabIndex);
            
            if (auto editor = dynamic_cast<DocumentQt*>(widget)) {
                presenter->onCloseDocument(editor);
            }
        });
        */

        return document;
    }

    void QMdiDocumentManager::setCurrentDocument(Document *document) {
        assert(mMdiArea);
        assert(document);
        
        auto documentQt = static_cast<DocumentQt*>(document);
        auto subWindowIt = documentSubWindowMap.find(documentQt);
        assert(subWindowIt != documentSubWindowMap.end());
        assert(subWindowIt->second);

        mMdiArea->setActiveSubWindow(subWindowIt->second);
    }

    Document* QMdiDocumentManager::getCurrentDocument() {
        assert(mMdiArea);

        if (auto subWindow = mMdiArea->activeSubWindow(); subWindow) {
            return static_cast<DocumentQt*>(subWindow->widget());
        }

        return nullptr;
    }

    std::size_t QMdiDocumentManager::getDocumentCount() const {
        assert(mMdiArea);

        return mMdiArea->subWindowList().count();
    }

    Document* QMdiDocumentManager::getDocument(const std::size_t index) {
        assert(mMdiArea);

        auto list = mMdiArea->subWindowList();
        auto subWindow = list[index];

        assert(subWindow);
        
        return static_cast<DocumentQt*>(subWindow->widget());
    }
    
    void QMdiDocumentManager::closeDocument(Document *document) {
        assert(mMdiArea);
        assert(document);

        auto documentQt = static_cast<DocumentQt*>(document);
        auto subWindowIt = documentSubWindowMap.find(documentQt);
        assert(subWindowIt != documentSubWindowMap.end());

        subWindowIt->second->close();
    }

    void QMdiDocumentManager::showDocument(Document *document) {
        assert(mMdiArea);
        assert(document);

        auto documentQt = static_cast<DocumentQt*>(document);
        auto subWindowIt = documentSubWindowMap.find(documentQt);
        assert(subWindowIt != documentSubWindowMap.end());

        subWindowIt->second->show();
    }
}
