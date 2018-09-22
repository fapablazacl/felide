
#ifndef __FELIDE_UI_MAINLOOPIMPL_HPP__
#define __FELIDE_UI_MAINLOOPIMPL_HPP__

#include <felide/ui/MainLoop.hpp>
#include <QApplication>

namespace felide {
    /**
     * @brief UI-Toolkit main loop / application abstraction
     */
    class MainLoopImpl : public MainLoop {
    public:
        explicit MainLoopImpl(int argc, char **argv);
        virtual ~MainLoopImpl();

        virtual int run() override;

    private:
        QApplication m_app;
    };
}

#endif
