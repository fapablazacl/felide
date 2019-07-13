
#ifndef __FELIDE_UI_UITOOLKIT_HPP__
#define __FELIDE_UI_UITOOLKIT_HPP__

#include <memory>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API IDEFramePresenter;
    class FELIDE_API UIToolkit {
    public:
        virtual ~UIToolkit();

        virtual int runApp(int argc, char **argv) = 0;
    };
}

#endif
