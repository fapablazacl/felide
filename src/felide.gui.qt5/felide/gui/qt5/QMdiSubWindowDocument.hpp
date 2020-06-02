
#pragma once

#include <QMdiSubWindow>

namespace felide {
    class DocumentManagerPresenter;

    class DocumentQt;
    class QMdiSubWindowDocument : public QMdiSubWindow {
        Q_OBJECT

    public:
        QMdiSubWindowDocument(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

        void closeEvent() override;
    };
}
