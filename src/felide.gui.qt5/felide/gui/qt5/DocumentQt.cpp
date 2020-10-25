
#include "DocumentQt.hpp"
#include "DocumentManagerQt.hpp"

#include <cassert>
#include <iostream>
#include <QLayout>
#include <QTabWidget>

#include <felide/gui/document/DocumentPresenter.hpp>

namespace felide {
    DocumentQt::DocumentQt(DocumentPresenter *presenter) : mDialogManager(this) {
        this->mPresenter = presenter;
        mScintilla = new QsciScintilla(this);
        mScintilla->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, false);
        mScintilla->setMarginWidth(1, QString("1000"));

        this->setupLayout();

        presenter->onInitialized(this, &mDialogManager);

        mScintilla->setFocus();

        // HACK: This prevents the raise of the textChanged signal, just only for the 1st time.
        this->setupSignals();
    }

    DocumentQt::~DocumentQt() {}

    void DocumentQt::setupSignals() {
        connect(mScintilla, &QsciScintilla::textChanged, [this]() {
            this->mPresenter->onContentChanged();
        });
    }

    void DocumentQt::setupLayout() {
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(mScintilla);
        this->setLayout(layout);
    }

    void DocumentQt::setTitle(const std::string &title) {
        if (auto subWindow = dynamic_cast<QMdiSubWindow *>(parentWidget())) {
            subWindow->setWindowTitle(title.c_str());
            mTitle = title;
        }
    }

    std::string DocumentQt::getTitle() const {
        return mTitle;
    }

    void DocumentQt::setContent(const std::string &content)  {
        mScintilla->setText(content.c_str());
    }

    std::string DocumentQt::getContent() const  {
        return mScintilla->text().toStdString();
    }

    void DocumentQt::setConfig(const DocumentConfig &config)  {
        assert(mScintilla);

        auto font = QFont{config.fontName.c_str(), config.fontSize};

        mScintilla->setFont(font);
        mScintilla->setCaretLineVisible(config.caretLineVisible);
        mScintilla->setTabWidth(config.tabWidth);

        if (config.showLineNumbers) {
            mScintilla->setMarginType(1, QsciScintilla::NumberMargin);
        }

        mConfig = config;
    }

    DocumentConfig DocumentQt::getConfig() const  {
        assert(mScintilla);

        return mConfig;
    }

    void DocumentQt::undo()  {
        assert(mScintilla);
        mScintilla->undo();
    }

    void DocumentQt::redo()  {
        assert(mScintilla);
        mScintilla->redo();
    }

    void DocumentQt::cut()  {
        assert(mScintilla);
        mScintilla->cut();
    }

    void DocumentQt::copy()  {
        assert(mScintilla);
        mScintilla->copy();
    }

    void DocumentQt::paste()  {
        assert(mScintilla);
        mScintilla->paste();
    }

    void DocumentQt::clearAll()  {
        // TODO: Add implementation
    }

    void DocumentQt::clearUndoBuffer()  {
        // TODO: Add implementation
    }

    void DocumentQt::setSelection(const TextSelection &selection) {
        // TODO: Add implementation
    }

    void DocumentQt::selectAll() {
        // TODO: Add implementation
    }

    void DocumentQt::clearSelection() {
        // TODO: Add implementation
    }

    TextSelection DocumentQt::getSelection() const {
        // TODO: Add implementation
        return TextSelection::all();
    }
}
