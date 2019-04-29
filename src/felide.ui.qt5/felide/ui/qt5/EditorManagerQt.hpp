
#ifndef __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_
#define __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_

#include <QWidget>
#include <QTabWidget>
#include <boost/optional.hpp>
#include <felide/ui/editor-manager/EditorManager.hpp>

namespace felide {
    class DocumentQt;
    class Document;
    class DocumentManagerQt : public QWidget, public DocumentManager {
        Q_OBJECT

    public:
        explicit DocumentManagerQt(QWidget *parent, DocumentManagerController *presenter);

        virtual ~DocumentManagerQt();
        
    public:
        boost::optional<int> getEditorIndex(const DocumentQt *editor);
        
        void changeEditorTitle(DocumentQt *editor, const std::string &title);
        
    signals:
        void editorContentChanged(DocumentQt *editor);
        
        void editorCloseRequested(DocumentQt *editor);

    public:
        virtual Document* appendEditor() override;

        virtual Document* getCurrentEditor() override;

        virtual std::size_t getEditorCount() const override;

        virtual Document* getEditor(const std::size_t index) override;
        
        virtual void closeEditor(Document *editorView) override;

        virtual void showEditor(Document *editorView) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
