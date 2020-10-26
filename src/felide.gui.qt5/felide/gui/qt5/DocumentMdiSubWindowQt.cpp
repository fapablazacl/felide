
#include "DocumentMdiSubWindowQt.hpp"

#include <cassert>
#include <iostream>

#include <QEvent>
#include <QGridLayout>


namespace felide {
    DocumentMdiSubWindowQt::DocumentMdiSubWindowQt(DocumentPresenter *presenter) : mDialogManager(this) {
        mPresenter = presenter;

        mScintilla = new QsciScintilla(this);
        mScintilla->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, false);
        mScintilla->setMarginWidth(1, QString("1000"));

        this->setWidget(mScintilla);

        // this->setupLayout();

        presenter->onInitialized(this, &mDialogManager);

        // HACK: This prevents the raise of the textChanged signal, just only for the 1st time.
        this->setupSignals();
    }


    DocumentMdiSubWindowQt::~DocumentMdiSubWindowQt() {}


    void DocumentMdiSubWindowQt::closeEvent(QCloseEvent *evt) {
        emit closeRequested(this, evt);
    }


    void DocumentMdiSubWindowQt::setupSignals() {
        connect(mScintilla, &QsciScintilla::textChanged, [this]() {
            this->mPresenter->onContentChanged();
        });
    }


    void DocumentMdiSubWindowQt::setupLayout() {
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(mScintilla);
        this->setLayout(layout);
    }


    void DocumentMdiSubWindowQt::setTitle(const std::string &title) {
        this->setWindowTitle(title.c_str());
    }


    std::string DocumentMdiSubWindowQt::getTitle() const {
        return this->windowTitle().toStdString();
    }


    void DocumentMdiSubWindowQt::setContent(const std::string &content)  {
        mScintilla->setText(content.c_str());
    }


    std::string DocumentMdiSubWindowQt::getContent() const  {
        return mScintilla->text().toStdString();
    }


    void DocumentMdiSubWindowQt::setConfig(const DocumentConfig &config)  {
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


    DocumentConfig DocumentMdiSubWindowQt::getConfig() const  {
        assert(mScintilla);

        return mConfig;
    }


    void DocumentMdiSubWindowQt::undo()  {
        assert(mScintilla);
        mScintilla->undo();
    }


    void DocumentMdiSubWindowQt::redo()  {
        assert(mScintilla);
        mScintilla->redo();
    }


    void DocumentMdiSubWindowQt::cut()  {
        assert(mScintilla);
        mScintilla->cut();
    }


    void DocumentMdiSubWindowQt::copy()  {
        assert(mScintilla);
        mScintilla->copy();
    }


    void DocumentMdiSubWindowQt::paste()  {
        assert(mScintilla);
        mScintilla->paste();
    }


    void DocumentMdiSubWindowQt::clearAll()  {
        // TODO: Add implementation
    }


    void DocumentMdiSubWindowQt::clearUndoBuffer()  {
        // TODO: Add implementation
    }


    void DocumentMdiSubWindowQt::setSelection(const TextSelection &selection) {
        // TODO: Add implementation
    }


    void DocumentMdiSubWindowQt::selectAll() {
        // TODO: Add implementation
    }


    void DocumentMdiSubWindowQt::clearSelection() {
        // TODO: Add implementation
    }


    TextSelection DocumentMdiSubWindowQt::getSelection() const {
        // TODO: Add implementation
        return TextSelection::all();
    }
}
