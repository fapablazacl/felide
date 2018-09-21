
#ifndef __FELIDE_UI_UIMANAGER_HPP__
#define __FELIDE_UI_UIMANAGER_HPP__

#include <memory>

namespace felide {
    class MainWindowView;
    class MainLoop;

    class ViewFactory {
    public:
        virtual ~ViewFactory();

        virtual std::unique_ptr<MainWindowView> createMainWindow() = 0;

        virtual std::unique_ptr<MainLoop> createMainLoop(int argc, char **argv) = 0;
    };

    template<typename MainWindowImpl, typename MainLoopImpl>
    class ViewFactoryImpl : public ViewFactory {
    public:
        virtual ~ViewFactoryImpl() {}

        virtual std::unique_ptr<MainWindowView> createMainWindow() override {
            return std::make_unique<MainWindowImpl>();
        }

        virtual std::unique_ptr<MainLoop> createMainLoop(int argc, char **argv) override {
            return std::make_unique<MainLoopImpl>(argc, argv);
        }
    };
}

#endif
