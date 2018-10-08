
#ifndef __FELIDE_UI_QT5_EDITOR_HPP_
#define __FELIDE_UI_QT5_EDITOR_HPP_

#include <QWidget>
#include <QTabWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>

#include <felide/ui/Editor.hpp>

namespace felide {
    class EditorManagerQt;
    class EditorQt : public QWidget, public Editor {
        Q_OBJECT

    public:
        explicit EditorQt(QWidget *parent, EditorManagerQt *editorManager);
        virtual ~EditorQt();

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

        virtual void setConfig(const EditorConfig &config) override;
        virtual EditorConfig getConfig() const override;

        virtual void undo() override;
        virtual void redo() override;

        virtual void cut() override;
        virtual void copy() override;
        virtual void paste() override;

        virtual void clearAll() override;

        virtual void clearUndoBuffer() override;

    private:
        EditorManagerQt *m_editorManager = nullptr;
        QsciScintilla *m_scintilla = nullptr;
        std::string m_title;
        EditorConfig m_config;
    };
}

#endif
