
#include "QMdiSubWindowDocument.hpp"

#include <cassert>
#include <QMdiSubWindow>
#include <QEvent>

namespace felide {
    QMdiSubWindowDocument::QMdiSubWindowDocument(QWidget *parent, Qt::WindowFlags flags) : QMdiSubWindow(parent, flags) {}

    /*
    QMdiSubWindowEventFilter::QMdiSubWindowEventFilter(QObject *parent, DocumentManagerPresenter *documentManagerPresenter) 
            : QObject(parent), documentManagerPresenter(documentManagerPresenter) {
        assert(documentManagerPresenter);
    }


    bool QMdiSubWindowEventFilter::eventFilter(QObject *obj, QEvent *event) {
        switch (event->type()) {
            case QEvent::Close: {
                auto subWindow = dynamic_cast<QMdiSubWindow*>(obj);
                assert(subWindow);
                
                break;
            }

            default: {
                qt_noop();
            }
        }

        return QObject::eventFilter(obj, event);
    }
    */
}
