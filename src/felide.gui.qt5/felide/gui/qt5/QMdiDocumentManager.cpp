
#include "QMdiDocumentManager.hpp"


#include <iostream>
#include <QGridLayout>
#include <QAction>
#include <QMenu>
#include <QMdiSubWindow>

#include <felide/gui/document/DocumentPresenter.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>

#include "DocumentQt.hpp"

namespace felide {
    QMdiDocumentManager::QMdiDocumentManager(QWidget *parent, DocumentManagerPresenter *presenter) : QWidget(parent), DocumentManager(presenter), dialogManager(this) {
        mdiArea = new QMdiArea(this);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabsMovable(true);

        /*
        connect(m_tabWidget, &QTabWidget::tabCloseRequested, [=] (int tabIndex) {
            QWidget *widget = m_tabWidget->widget(tabIndex);
            
            if (auto editor = dynamic_cast<DocumentQt*>(widget)) {
                presenter->onCloseDocument(editor);
            }
        });
        */

        /*
        m_tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_tabWidget, &QTabWidget::customContextMenuRequested, [this](const QPoint &pos) {
            bool found = false;
            int index = 0;

            // determine the tab
            for (int i=0; i<m_tabWidget->count(); i++) {
                const auto rect = m_tabWidget->tabBar()->tabRect(i);

                if (rect.contains(pos)) {
                    found = true;
                    index = i;
                    break;
                }
            }

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
        */

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(mdiArea);
        this->setLayout(layout);

        presenter->onInitialized(this, &dialogManager);
    }

    QMdiDocumentManager::~QMdiDocumentManager() {}
    
    boost::optional<int> QMdiDocumentManager::getDocumentIndex(const DocumentQt *editor) {
        return {};
    }
    
    void QMdiDocumentManager::changeDocumentTitle(DocumentQt *editor, const std::string &title) {

    }
}

namespace felide {
    Document* QMdiDocumentManager::appendDocument(DocumentPresenter *documentPresenter) {
        auto subWindow = new QMdiSubWindow();

        subWindow->setWidget(new QWidget(subWindow));
        subWindow->setAttribute(Qt::WA_DeleteOnClose);

        mdiArea->addSubWindow(subWindow);

        return nullptr;
    }

    void QMdiDocumentManager::setCurrentDocument(Document *document) {

    }

    Document* QMdiDocumentManager::getCurrentDocument() {
        return nullptr;
    }

    std::size_t QMdiDocumentManager::getDocumentCount() const {
        return 0;
    }

    Document* QMdiDocumentManager::getDocument(const std::size_t index) {
        return nullptr;
    }
    
    void QMdiDocumentManager::closeDocument(Document *editorView) {
        
    }

    void QMdiDocumentManager::showDocument(Document *editorView) {

    }
}
