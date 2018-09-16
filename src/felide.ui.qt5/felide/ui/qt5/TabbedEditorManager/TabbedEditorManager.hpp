
#ifndef __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_
#define __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_

#include <QWidget>
#include <QTabWidget>
#include <boost/optional.hpp>
#include "EditorManagerView.hpp"

namespace felide {
    class Editor;
    class EditorView;
    class TabbedEditorManager : public QWidget, public EditorManagerView {
        Q_OBJECT

    public:
        explicit TabbedEditorManager(QWidget *parent);

        virtual ~TabbedEditorManager();
        
    public:
        boost::optional<int> getEditorIndex(const Editor *editor);
        
        void changeEditorTitle(Editor *editor, const std::string &title);
        
    signals:
        void editorContentChanged(Editor *editor);
        
        void editorCloseRequested(Editor *editor);

    public:
        virtual EditorView* appendEditor() override;

        virtual EditorView* getCurrentEditor() override;

        virtual std::size_t getEditorCount() const override;

        virtual EditorView* getEditor(const std::size_t index) override;
        
        virtual void closeEditor(EditorView *editorView) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
