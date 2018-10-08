
#ifndef __FELIDE_UI_QT5_VIEWFACTORYQT5_HPP__
#define __FELIDE_UI_QT5_VIEWFACTORYQT5_HPP__

#include <felide/ui/UIToolkit.hpp>

namespace felide {
    class UIToolkitQt : public UIToolkit {
    public:
        virtual int runApp(int argc, char **argv, MainWindowPresenter *presenter) override;
    };
}

#endif
