
#include "DocumentQt.hpp"
#include "DocumentManagerQt.hpp"

#include <cassert>
#include <iostream>
#include <QLayout>

#include <felide/ui/document/DocumentPresenter.hpp>

namespace felide {
    DocumentQt::DocumentQt(QWidget *parent, DocumentPresenter *presenter, DocumentManagerQt *documentManager) : QWidget(parent) {
        this->documentManager = documentManager;
        this->presenter = presenter;
        m_scintilla = new QsciScintilla(this);
        m_scintilla->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, false);
        m_scintilla->setMarginWidth(1, QString("1000"));

        this->setupScintilla();
        this->setupLayout();

        m_scintilla->setFocus();

        presenter->onInitialized(this);
    }

    DocumentQt::~DocumentQt() {}

    void DocumentQt::setupScintilla() {
        connect(m_scintilla, &QsciScintilla::textChanged, [this]() {
            this->presenter->onContentChanged();
        });
    }

    void DocumentQt::setupLayout() {
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(m_scintilla);
        this->setLayout(layout);
    }

    void DocumentQt::setTitle(const std::string &title) {
        documentManager->changeDocumentTitle(this, title);
    }

    std::string DocumentQt::getTitle() const {
        return m_title;
    }

    void DocumentQt::setContent(const std::string &content)  {
        m_scintilla->setText(content.c_str());
    }

    std::string DocumentQt::getContent() const  {
        return m_scintilla->text().toStdString();
    }

    void DocumentQt::setConfig(const DocumentConfig &config)  {
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

    DocumentConfig DocumentQt::getConfig() const  {
        assert(m_scintilla);

        return m_config;
    }

    void DocumentQt::undo()  {
        assert(m_scintilla);
        m_scintilla->undo();
    }

    void DocumentQt::redo()  {
        assert(m_scintilla);
        m_scintilla->redo();
    }

    void DocumentQt::cut()  {
        assert(m_scintilla);
        m_scintilla->cut();
    }

    void DocumentQt::copy()  {
        assert(m_scintilla);
        m_scintilla->copy();
    }

    void DocumentQt::paste()  {
        assert(m_scintilla);
        m_scintilla->paste();
    }

    void DocumentQt::clearAll()  {
        // TODO: Add implementation
    }

    void DocumentQt::clearUndoBuffer()  {
        // TODO: Add implementation
    }
}
