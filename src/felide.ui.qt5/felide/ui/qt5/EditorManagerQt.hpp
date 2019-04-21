
#ifndef __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_
#define __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_

#include <QWidget>
#include <QTabWidget>
#include <boost/optional.hpp>
#include <felide/ui/editor-manager/EditorManager.hpp>

namespace felide {
    class EditorQt;
    class Editor;
    class EditorManagerQt : public QWidget, public EditorManager {
        Q_OBJECT

    public:
        explicit EditorManagerQt(QWidget *parent, EditorManagerPresenter *presenter);

        virtual ~EditorManagerQt();
        
    public:
        boost::optional<int> getEditorIndex(const EditorQt *editor);
        
        void changeEditorTitle(EditorQt *editor, const std::string &title);
        
    signals:
        void editorContentChanged(EditorQt *editor);
        
        void editorCloseRequested(EditorQt *editor);

    public:
        virtual Editor* appendEditor() override;

        virtual Editor* getCurrentEditor() override;

        virtual std::size_t getEditorCount() const override;

        virtual Editor* getEditor(const std::size_t index) override;
        
        virtual void closeEditor(Editor *editorView) override;

        virtual void showEditor(Editor *editorView) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
