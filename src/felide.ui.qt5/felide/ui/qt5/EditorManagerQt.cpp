
#include "EditorManagerQt.hpp"

#include <iostream>
#include <QGridLayout>
#include <QTabBar>
#include <QAction>
#include <QMenu>
#include <felide/ui/EditorManagerPresenter.hpp>

#include "EditorQt.hpp"

namespace felide {
    EditorManagerQt::EditorManagerQt(QWidget *parent, EditorManagerPresenter *presenter) : QWidget(parent), EditorManager(presenter) {
        m_tabWidget = new QTabWidget(this);
        m_tabWidget->setTabsClosable(true);
        m_tabWidget->setDocumentMode(true);
        
        connect(m_tabWidget, &QTabWidget::tabCloseRequested, [=] (int tabIndex) {
            QWidget *widget = m_tabWidget->widget(tabIndex);
            
            auto editor = dynamic_cast<EditorQt*>(widget);
            if (editor) {
                editorCloseRequested(editor);
            }
        });

        m_tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_tabWidget, &QTabWidget::customContextMenuRequested, [this](const QPoint &pos) {
            bool found = false;

            // determine the tab
            for (int i=0; i<m_tabWidget->count(); i++) {
                const auto rect = m_tabWidget->tabBar()->tabRect(i);

                if (rect.contains(pos)) {
                    found = true;
                    break;
                }
            }

            // trigger context menu on that tab
            if (found) {
                QMenu contextMenu("Context Menu", this);
                QAction renameAction("Rename", this);

                contextMenu.addAction(&renameAction);

                this->connect(&renameAction, &QAction::triggered, [this]() {
                    std::cout << "Test!" << std::endl;
                });

                contextMenu.exec(this->mapToGlobal(pos));
            }
        });

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_tabWidget);
        this->setLayout(layout);

        m_presenter->attachView(this);
    }

    EditorManagerQt::~EditorManagerQt() {}
    
    boost::optional<int> EditorManagerQt::getEditorIndex(const EditorQt *editor) {
        for (int i=0; i<m_tabWidget->count(); i++) {
            if (m_tabWidget->widget(i) == editor) {
                return i;
            }
        }
        
        return {};
    }
    
    void EditorManagerQt::changeEditorTitle(EditorQt *editor, const std::string &title) {
        auto index = this->getEditorIndex(editor);
        
        if (!index) {
            return;
        }
        
        m_tabWidget->setTabText(*index, title.c_str());
    }

    Editor* EditorManagerQt::appendEditor() {
        auto editor = new EditorQt(m_tabWidget, this);

        connect(editor, &EditorQt::contentChanged, [=]() {
            editorContentChanged(editor);
        });
        
        m_tabWidget->addTab(editor, "");
        m_tabWidget->setCurrentWidget(editor);

        return editor;
    }

    Editor* EditorManagerQt::getCurrentEditor() {
        QWidget *widget = m_tabWidget->currentWidget();

        if (!widget) {
            return nullptr;
        }

        return dynamic_cast<Editor*>(widget);
    }

    std::size_t EditorManagerQt::getEditorCount() const {
        return static_cast<std::size_t>(m_tabWidget->count());
    }

    Editor* EditorManagerQt::getEditor(const std::size_t index) {
        return dynamic_cast<Editor*>(m_tabWidget->widget(static_cast<int>(index)));
    }
    
    void EditorManagerQt::closeEditor(Editor *editorView) {
        const auto editor = dynamic_cast<EditorQt*>(editorView);
        
        if (!editor) {
            return;
        }
        
        const auto index = this->getEditorIndex(editor);
        
        if (!index) {
            return;
        }
        
        m_tabWidget->removeTab(*index);
    }

    void EditorManagerQt::showEditor(Editor *editorView) {
        const auto editor = dynamic_cast<EditorQt*>(editorView);

        if (!editor) {
            return;
        }
        
        const auto index = this->getEditorIndex(editor);
        
        if (!index) {
            return;
        }

        m_tabWidget->setCurrentIndex(*index);
    }
}
