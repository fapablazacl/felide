
#include "EditorManagerQt.hpp"

#include <QGridLayout>
#include "EditorQt.hpp"

namespace felide {
    EditorManagerQt::EditorManagerQt(QWidget *parent) : QWidget(parent) {
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

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_tabWidget);
        this->setLayout(layout);
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
