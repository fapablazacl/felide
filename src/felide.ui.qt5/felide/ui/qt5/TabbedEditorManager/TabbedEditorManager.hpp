
#ifndef __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_
#define __FELIDE_UI_QT5_TABBEDEDITORMANAGER_HPP_

#include <QWidget>
#include <QTabWidget>
#include "../MainWindow/MainWindowView.hpp"

namespace felide {
    class TabbedEditorManager : public QWidget, public EditorManagerView {
        Q_OBJECT

    public:
        explicit TabbedEditorManager(QWidget *parent);

        virtual ~TabbedEditorManager();

    signals:
        void editorContentChanged(EditorView *viewChanged);

    public:
        // EditorManagerView implementation
        virtual EditorView* appendEditor() override;

        virtual EditorView* getCurrentEditor() override;

        virtual std::size_t getEditorCount() const override;

        virtual EditorView* getEditor(const std::size_t index) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
