
#ifndef __FELIDE_UI_QT5_EDITOR_HPP_
#define __FELIDE_UI_QT5_EDITOR_HPP_

#include <QWidget>
#include <QTabWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>

#include <felide/gui/document/Document.hpp>

#include "DialogManagerQt.hpp"

namespace felide {
    class DocumentPresenter;

    class DocumentManagerQt;
    class DocumentQt : public QWidget, public Document {
        Q_OBJECT

    public:
        explicit DocumentQt(QTabWidget *parentTabWidget, DocumentPresenter *presenter, DocumentManagerQt *documentManager);

        virtual ~DocumentQt();

    private:
        void setupSignals();

        void setupLayout();

    public:
        virtual void setTitle(const std::string &title) override;
        virtual std::string getTitle() const override;

        virtual void setContent(const std::string &content) override;
        virtual std::string getContent() const override;

        virtual void setConfig(const DocumentConfig &config) override;
        virtual DocumentConfig getConfig() const override;

        virtual void undo() override;
        virtual void redo() override;

        virtual void cut() override;
        virtual void copy() override;
        virtual void paste() override;

        virtual void clearAll() override;

        virtual void clearUndoBuffer() override;

        virtual void setSelection(const TextSelection &selection) override;

        virtual void selectAll() override;

        virtual void clearSelection() override;

        virtual TextSelection getSelection() const override;

    private:
        DialogManagerQt dialogManager;
        DocumentManagerQt *documentManager = nullptr;
        DocumentPresenter *presenter = nullptr;
        QsciScintilla *m_scintilla = nullptr;
        std::string m_title;
        DocumentConfig m_config;
    };
}

#endif
