
#pragma once

#include <QObject>
#include <QMdiSubWindow>
#include <QCloseEvent>

namespace felide {
    // TODO: Consider promote this class to be the Document interface implementation
    class EnhancedMdiSubWindow : public QMdiSubWindow {
        Q_OBJECT

    signals:
        void closeRequested(EnhancedMdiSubWindow *subWindow, QCloseEvent *evt);

    public:
        void closeEvent(QCloseEvent *evt) override;
    };
}
