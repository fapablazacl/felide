
#include "QMdiSubWindowDocument.hpp"

#include <cassert>
#include <QMdiSubWindow>
#include <QEvent>

namespace felide {
    QMdiSubWindowDocument::QMdiSubWindowDocument(QWidget *parent, DocumentQt *widget): QMdiSubWindow(parent, {}) {
        this->setWidget(widget);
    }

    void QMdiSubWindowDocument::setWidget(DocumentQt *widget) {
         QMdiSubWindow::setWidget(widget);
    }

    DocumentQt* QMdiSubWindowDocument::widget() const {
        return static_cast<DocumentQt*>(QMdiSubWindow::widget());
    }

    void QMdiSubWindowDocument::closeEvent(QCloseEvent *event) {
        QMdiSubWindow::closeEvent(event);
    }
}
