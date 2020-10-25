
#include "QMdiSubWindowDocument.hpp"

#include <cassert>
#include <QEvent>
#include <iostream>

namespace felide {
    MdiSubWindowEventFilter::MdiSubWindowEventFilter(QObject *parent) 
        : QObject(parent) {}

    bool MdiSubWindowEventFilter::eventFilter(QObject *obj, QEvent *evt) {
        switch (evt->type()) {
        case QEvent::Close:
            if (auto subWindow = dynamic_cast<QMdiSubWindow*>(obj); subWindow) {
                // notify that we want to close the SubWindow
                std::cout << "asdasda" << std::endl;
                evt->ignore();
                return true;
            }

            break;

        default:
            qt_noop();
        }

        return QObject::eventFilter(obj, evt);
    }
}
