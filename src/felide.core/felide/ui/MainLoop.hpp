
#ifndef __FELIDE_UI_MAINLOOP_HPP__
#define __FELIDE_UI_MAINLOOP_HPP__

#include <felide/Predef.hpp>

namespace felide {
    /**
     * @brief UI-Toolkit main loop abstraction
     */
    class FELIDE_API MainLoop {
    public:
        virtual ~MainLoop();

        virtual int run() = 0;
    };
}

#endif
