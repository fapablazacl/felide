
#ifndef __FELIDE_UI_QT5_UTILITIESQT_HPP__
#define __FELIDE_UI_QT5_UTILITIESQT_HPP__

#include <QMenuBar>
#include <Xenoide/GUI/Menu.hpp>

namespace felide {
    extern void setupMenu(QMenu *parentMenuPtr, const Menu &menu);

    extern QMenuBar* createMenuBar(QWidget *parent, const Menu &menuBar);
}

#endif
