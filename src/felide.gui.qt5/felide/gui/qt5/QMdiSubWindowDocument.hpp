
#pragma once

#include <QObject>
#include <QMdiSubWindow>

namespace felide {
    class MdiSubWindowEventFilter : public QObject {
        Q_OBJECT

    signals:

    public:
        MdiSubWindowEventFilter(QObject *parent);

        bool eventFilter(QObject *obj, QEvent *evt) override;
    };
}
