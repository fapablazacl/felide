
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

    public:
        // EditorManagerView implementation
        virtual EditorView* appendEditor() override;

        virtual EditorView* getCurrentEditor() override;

    private:
        QTabWidget *m_tabWidget = nullptr;
    };
} 

#endif
