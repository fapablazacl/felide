
#ifndef __FELIDE_UI_UITOOLKIT_HPP__
#define __FELIDE_UI_UITOOLKIT_HPP__

#include <memory>
#include <felide/Predef.hpp>
#include <felide/ui/MainWindowView.hpp>
#include <felide/ui/MainLoop.hpp>

namespace felide {
    class MainWindowView;
    class MainLoop;

    class FELIDE_API UIToolkit {
    public:
        virtual ~UIToolkit();

        virtual std::unique_ptr<MainWindowView> createMainWindow() = 0;

        virtual std::unique_ptr<MainLoop> createMainLoop(int argc, char **argv) = 0;

        virtual int runApp(int argc, char **argv) = 0;
    };

    template<typename MainWindowImpl, typename MainLoopImpl>
    class UIToolkitImpl : public UIToolkit {
    public:
        virtual ~UIToolkitImpl() {}

        virtual std::unique_ptr<MainWindowView> createMainWindow() override {
            return std::make_unique<MainWindowImpl>();
        }

        virtual std::unique_ptr<MainLoop> createMainLoop(int argc, char **argv) override {
            return std::make_unique<MainLoopImpl>(argc, argv);
        }
    };
}

#endif
