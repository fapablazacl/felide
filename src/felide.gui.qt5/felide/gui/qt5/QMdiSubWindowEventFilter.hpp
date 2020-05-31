
#pragma once

#include <QObject>

namespace felide {
    class DocumentManagerPresenter;

    class QMdiSubWindowEventFilter : public QObject {
        Q_OBJECT

    public:
        QMdiSubWindowEventFilter(QObject *parent, DocumentManagerPresenter *documentManagerPresenter);

        bool eventFilter(QObject *obj, QEvent *event) override;

    private:
        DocumentManagerPresenter *documentManagerPresenter = nullptr;
    };
}
