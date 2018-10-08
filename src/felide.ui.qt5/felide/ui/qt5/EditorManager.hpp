
#ifndef __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_
#define __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_

#include <QWidget>
#include <QTabWidget>
#include <boost/optional.hpp>
#include <felide/ui/EditorManagerView.hpp>

namespace felide {
    class EditorQt;
    class EditorView;
    class EditorManager : public QWidget, public EditorManagerView {
        Q_OBJECT

    public:
        explicit EditorManager(QWidget *parent);

        virtual ~EditorManager();
        
    public:
        boost::optional<int> getEditorIndex(const EditorQt *editor);
        
        void changeEditorTitle(EditorQt *editor, const std::string &title);
        
    signals:
        void editorContentChanged(EditorQt *editor);
        
        void editorCloseRequested(EditorQt *editor);

    public:
        virtual EditorView* appendEditor() override;

        virtual EditorView* getCurrentEditor() override;

        virtual std::size_t getEditorCount() const override;

        virtual EditorView* getEditor(const std::size_t index) override;
        
        virtual void closeEditor(EditorView *editorView) override;

        virtual void showEditor(EditorView *editorView) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
