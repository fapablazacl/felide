
#include "DocumentManagerQt.hpp"

#include <iostream>
#include <QGridLayout>
#include <QTabBar>
#include <QAction>
#include <QMenu>
#include <felide/ui/document-manager/DocumentManagerPresenter.hpp>

#include "DocumentQt.hpp"

namespace felide {
    DocumentManagerQt::DocumentManagerQt(QWidget *parent, DocumentManagerPresenter *controller) : QWidget(parent), DocumentManager(controller) {
        m_tabWidget = new QTabWidget(this);
        m_tabWidget->setTabsClosable(true);
        m_tabWidget->setDocumentMode(true);
        
        connect(m_tabWidget, &QTabWidget::tabCloseRequested, [=] (int tabIndex) {
            QWidget *widget = m_tabWidget->widget(tabIndex);
            
            auto editor = dynamic_cast<DocumentQt*>(widget);
            if (editor) {
                editorCloseRequested(editor);
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

            // TODO: Generate menu Dinamically
            // trigger context menu on that tab
            if (found) {
                Document *editor = this->getDocument(index);
                QMenu contextMenu("Context Menu", this);

                QAction closeAction("Close", this);
                contextMenu.addAction(&closeAction);
                this->connect(&closeAction, &QAction::triggered, [this, editor]() {
                    m_presenter->onCloseDocument(editor);
                });

                QAction closeAllButThisAction("Close all but this", this);
                contextMenu.addAction(&closeAllButThisAction);
                this->connect(&closeAllButThisAction, &QAction::triggered, [this, editor]() {
                    m_presenter->onCloseOthers(editor);
                });

                QAction closeAllAction("Close all", this);
                contextMenu.addAction(&closeAllAction);
                this->connect(&closeAllAction, &QAction::triggered, [this]() {
                    m_presenter->onCloseAll();
                });

                QAction closeToTheRightAction("Close to the right", this);
                contextMenu.addAction(&closeToTheRightAction);
                this->connect(&closeToTheRightAction, &QAction::triggered, [this, editor]() {
                    m_presenter->onCloseToTheRight(editor);
                });

                contextMenu.exec(this->mapToGlobal(pos));
            }
        });

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_tabWidget);
        this->setLayout(layout);

        m_presenter->attachView(this);
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
        auto index = this->getDocumentIndex(editor);
        
        if (!index) {
            return;
        }
        
        m_tabWidget->setTabText(*index, title.c_str());
    }
}

namespace felide {
    Document* DocumentManagerQt::appendDocument(DocumentPresenter *presenter) {
        auto editor = new DocumentQt(m_tabWidget, presenter);

        m_tabWidget->addTab(editor, "");
        m_tabWidget->setCurrentWidget(editor);

        return editor;
    }

    Document* DocumentManagerQt::getCurrentDocument() {
        QWidget *widget = m_tabWidget->currentWidget();

        if (!widget) {
            return nullptr;
        }

        return dynamic_cast<Document*>(widget);
    }

    std::size_t DocumentManagerQt::getDocumentCount() const {
        return static_cast<std::size_t>(m_tabWidget->count());
    }

    Document* DocumentManagerQt::getDocument(const std::size_t index) {
        return dynamic_cast<Document*>(m_tabWidget->widget(static_cast<int>(index)));
    }
    
    void DocumentManagerQt::closeDocument(Document *editorView) {
        if(const auto editor = dynamic_cast<DocumentQt*>(editorView)) {
            if (const auto index = this->getDocumentIndex(editor)) {
                m_tabWidget->removeTab(*index);
            }
        }
    }

    void DocumentManagerQt::showDocument(Document *editorView) {
        if(const auto editor = dynamic_cast<DocumentQt*>(editorView)) {
            if (const auto index = this->getDocumentIndex(editor)) {
                m_tabWidget->setCurrentIndex(*index);
            }
        }
    }
}
