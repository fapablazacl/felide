
#ifndef __FELIDE_UI_UIMANAGER_HPP__
#define __FELIDE_UI_UIMANAGER_HPP__

namespace felide {
    class MainWindowView;

    class ViewFactory {
    public:
        virtual ~ViewFactory();
        virtual MainWindowView* createMainWindow() = 0;
    };

    template<typename MainWindowImpl>
    class ViewFactoryImpl : public ViewFactory {
    public:
        virtual ~ViewFactoryImpl() {}

        virtual MainWindowImpl* createMainWindow() override {
            return new MainWindowImpl();
        }
    };
}

#endif
