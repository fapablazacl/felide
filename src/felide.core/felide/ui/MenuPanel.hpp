
#ifndef __FELIDE_UI_MENUPANEL_HPP__
#define __FELIDE_UI_MENUPANEL_HPP__

#include <felide/Predef.hpp>

namespace felide {
    struct Menu;

    /**
     * @brief View that shows to the user a MenuBar.
     */
    class FELIDE_API MenuPanel {
    public:
        virtual ~MenuPanel();

        virtual void setupMenuBar(const Menu &menu) = 0;
    };
}

#endif
