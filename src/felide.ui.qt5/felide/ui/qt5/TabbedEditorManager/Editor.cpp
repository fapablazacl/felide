
#include "Editor.hpp"

#include <QLayout>
#include <cassert>

namespace felide {
    Editor::Editor(QWidget *parent) : QWidget(parent) {
        m_scintilla = new QsciScintilla(this);
        
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_scintilla);
        this->setLayout(layout);
    }

    Editor::~Editor() {}

    void Editor::setTitle(const std::string &title) {
        // TODO: Agregar implementacion
    }

    std::string Editor::getTitle() const  {
        // TODO: Agregar implementacion
        return "";
    }

    void Editor::setContent(const std::string &content)  {
        m_scintilla->setText(content.c_str());
    }

    std::string Editor::getContent() const  {
        return m_scintilla->text().toStdString();
    }

    void Editor::setConfig(const EditorConfig &config)  {
        assert(m_scintilla);

        auto font = QFont{config.fontName.c_str(), config.fontSize};

        m_scintilla->setFont(font);
        m_scintilla->setCaretLineVisible(config.caretLineVisible);
        m_scintilla->setTabWidth(config.tabWidth);

        m_config = config;
    }

    EditorConfig Editor::getConfig() const  {
        assert(m_scintilla);

        return m_config;
    }

    void Editor::undo()  {
        assert(m_scintilla);
        m_scintilla->undo();
    }

    void Editor::redo()  {
        assert(m_scintilla);
        m_scintilla->redo();
    }

    void Editor::cut()  {
        assert(m_scintilla);
        m_scintilla->cut();
    }

    void Editor::copy()  {
        assert(m_scintilla);
        m_scintilla->copy();
    }

    void Editor::paste()  {
        assert(m_scintilla);
        m_scintilla->paste();
    }

    void Editor::clearAll()  {
        // TODO: Agregar implementacion
    }

    void Editor::clearUndoBuffer()  {
        // TODO: Agregar implementacion
    }
}
