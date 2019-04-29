
#ifndef __FELIDE_UI_QT5_EDITOR_HPP_
#define __FELIDE_UI_QT5_EDITOR_HPP_

#include <QWidget>
#include <QTabWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>

#include <felide/ui/editor/Editor.hpp>

namespace felide {
    class DocumentManagerQt;
    class DocumentQt : public QWidget, public Document {
        Q_OBJECT

    public:
        explicit DocumentQt(QWidget *parent, DocumentManagerQt *editorManager);
        virtual ~DocumentQt();

    private:
        void setupScintilla();

        void setupLayout();

    signals:
        void contentChanged();

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

    private:
        DocumentManagerQt *m_editorManager = nullptr;
        QsciScintilla *m_scintilla = nullptr;
        std::string m_title;
        DocumentConfig m_config;
    };
}

#endif
