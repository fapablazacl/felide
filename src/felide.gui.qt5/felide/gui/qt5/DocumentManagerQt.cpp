
#include "DocumentManagerQt.hpp"

#include <iostream>
#include <QGridLayout>
#include <QTabBar>
#include <QAction>
#include <QMenu>

#include <felide/gui/document/DocumentPresenter.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>

#include "DocumentQt.hpp"

namespace felide {
    DocumentManagerQt::DocumentManagerQt(QWidget *parent, DocumentManagerPresenter *presenter) : QWidget(parent), DocumentManager(presenter), dialogManager(this) {
        m_tabWidget = new QTabWidget(this);
        m_tabWidget->setTabsClosable(true);
        m_tabWidget->setDocumentMode(true);
        
        connect(m_tabWidget, &QTabWidget::tabCloseRequested, [=] (int tabIndex) {
            QWidget *widget = m_tabWidget->widget(tabIndex);
            
            if (auto editor = dynamic_cast<DocumentQt*>(widget)) {
                presenter->onCloseDocument(editor);
            }
        });

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

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_tabWidget);
        this->setLayout(layout);

        presenter->onInitialized(this, &dialogManager);
    }

    DocumentManagerQt::~DocumentManagerQt() {}
    
    boost::optional<int> DocumentManagerQt::getDocumentIndex(const DocumentQt *editor) {
        for (int i=0; i<m_tabWidget->count(); i++) {
            if (m_tabWidget->widget(i) == editor) {
                return i;
            }
        }
        
        return {};
    }
    
    void DocumentManagerQt::changeDocumentTitle(DocumentQt *editor, const std::string &title) {
        if (auto index = this->getDocumentIndex(editor)) {
            m_tabWidget->setTabText(index.get(), title.c_str());
        }
    }
}

namespace felide {
    Document* DocumentManagerQt::appendDocument(DocumentPresenter *documentPresenter) {
        auto document = new DocumentQt(nullptr, documentPresenter);

        return document;
    }

    void DocumentManagerQt::setCurrentDocument(Document *document) {
        if (const auto editor = dynamic_cast<DocumentQt*>(document)) {
            if (const auto index = this->getDocumentIndex(editor)) {
                m_tabWidget->setCurrentIndex(index.get());
            }
        }
    }

    Document* DocumentManagerQt::getCurrentDocument() {
        if (QWidget *widget = m_tabWidget->currentWidget()) {
            return dynamic_cast<Document*>(widget);
        }

        return nullptr;
    }

    std::size_t DocumentManagerQt::getDocumentCount() const {
        return static_cast<std::size_t>(m_tabWidget->count());
    }

    Document* DocumentManagerQt::getDocument(const std::size_t index) {
        return dynamic_cast<Document*>(m_tabWidget->widget(static_cast<int>(index)));
    }
    
    void DocumentManagerQt::closeDocument(Document *editorView) {
        if (const auto editor = dynamic_cast<DocumentQt*>(editorView)) {
            if (const auto index = this->getDocumentIndex(editor)) {
                m_tabWidget->removeTab(index.get());
            }
        }
    }

    void DocumentManagerQt::showDocument(Document *editorView) {
        if (const auto editor = dynamic_cast<DocumentQt*>(editorView)) {
            if (const auto index = this->getDocumentIndex(editor)) {
                m_tabWidget->setCurrentIndex(index.get());
            }
        }
    }
}
