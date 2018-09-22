
#ifndef __FELIDE_UI_MAINLOOP_HPP__
#define __FELIDE_UI_MAINLOOP_HPP__

namespace felide {
    /**
     * @brief UI-Toolkit main loop abstraction
     */
    class MainLoop {
    public:
        virtual ~MainLoop();

        virtual int run() = 0;
    };
}

#endif
