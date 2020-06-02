
#pragma once

#include <QMdiSubWindow>

#include "DocumentQt.hpp"

namespace felide {
    class DocumentManagerPresenter;

    class QMdiSubWindowDocument : public QMdiSubWindow {
        Q_OBJECT

    public:
        QMdiSubWindowDocument(QWidget *parent = nullptr, DocumentQt *widget = nullptr);

        void setWidget(DocumentQt *widget);

        DocumentQt* widget() const;

        void closeEvent(QCloseEvent *event) override;
    };
}
