
#include "EditorQt.hpp"

#include <cassert>
#include <iostream>
#include <QLayout>
#include "EditorManager.hpp"

namespace felide {
    EditorQt::EditorQt(QWidget *parent, EditorManager *editorManager) : QWidget(parent) {
        m_editorManager = editorManager;
        m_scintilla = new QsciScintilla(this);
        m_scintilla->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, false);
        m_scintilla->setMarginWidth(1, QString("1000"));

        this->setupScintilla();
        this->setupLayout();

        m_scintilla->setFocus();
    }

    EditorQt::~EditorQt() {}

    void EditorQt::setupScintilla() {
        connect(m_scintilla, &QsciScintilla::textChanged, [this]() {
            contentChanged();
        });
    }

    void EditorQt::setupLayout() {
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_scintilla);
        this->setLayout(layout);
    }

    void EditorQt::setTitle(const std::string &title) {
        m_editorManager->changeEditorTitle(this, title);
    }

    std::string EditorQt::getTitle() const {
        return m_title;
    }

    void EditorQt::setContent(const std::string &content)  {
        m_scintilla->setText(content.c_str());
    }

    std::string EditorQt::getContent() const  {
        return m_scintilla->text().toStdString();
    }

    void EditorQt::setConfig(const EditorConfig &config)  {
        assert(m_scintilla);

        auto font = QFont{config.fontName.c_str(), config.fontSize};

        m_scintilla->setFont(font);
        m_scintilla->setCaretLineVisible(config.caretLineVisible);
        m_scintilla->setTabWidth(config.tabWidth);

        if (config.showLineNumbers) {
            m_scintilla->setMarginType(1, QsciScintilla::NumberMargin);
        }

        m_config = config;
    }

    EditorConfig EditorQt::getConfig() const  {
        assert(m_scintilla);

        return m_config;
    }

    void EditorQt::undo()  {
        assert(m_scintilla);
        m_scintilla->undo();
    }

    void EditorQt::redo()  {
        assert(m_scintilla);
        m_scintilla->redo();
    }

    void EditorQt::cut()  {
        assert(m_scintilla);
        m_scintilla->cut();
    }

    void EditorQt::copy()  {
        assert(m_scintilla);
        m_scintilla->copy();
    }

    void EditorQt::paste()  {
        assert(m_scintilla);
        m_scintilla->paste();
    }

    void EditorQt::clearAll()  {
        // TODO: Agregar implementacion
    }

    void EditorQt::clearUndoBuffer()  {
        // TODO: Agregar implementacion
    }
}
