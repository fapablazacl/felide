
#include "QMdiSubWindowDocument.hpp"

#include <cassert>
#include <QEvent>
#include <iostream>

namespace felide {
    void EnhancedMdiSubWindow::closeEvent(QCloseEvent *evt) {
        emit closeRequested(this, evt);
    }
}
