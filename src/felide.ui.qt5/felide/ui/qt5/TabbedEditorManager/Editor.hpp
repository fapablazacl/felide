
#ifndef __FELIDE_UI_QT5_EDITOR_HPP_
#define __FELIDE_UI_QT5_EDITOR_HPP_

#include <QWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>

#include "../MainWindow/MainWindowView.hpp"

namespace felide {
    class Editor : public QWidget, public EditorView {
        Q_OBJECT

    public:
        explicit Editor(QWidget *parent);
        virtual ~Editor();

        // EditorView implementation
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
        QsciScintilla *m_scintilla = nullptr;
        EditorConfig m_config;
    };
}

#endif
