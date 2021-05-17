
#ifndef __XENOIDE_UI_QT5_UTILITIESQT_HPP__
#define __XENOIDE_UI_QT5_UTILITIESQT_HPP__

#include <QMenuBar>
#include <Xenoide/Gui/Menu.hpp>

namespace Xenoide {
    extern void setupMenu(QMenu *parentMenuPtr, const Menu &menu);

    extern QMenuBar* createMenuBar(QWidget *parent, const Menu &menuBar);
}

#endif
