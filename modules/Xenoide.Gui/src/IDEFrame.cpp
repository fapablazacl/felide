
#include <Xenoide/Gui/IDEFrame.hpp>
#include <Xenoide/Gui/IDEFramePresenter.hpp>

#include <Xenoide/Gui/Menu.hpp>

namespace Xenoide {
    IDEFrame::IDEFrame(IDEFramePresenter *presenter) {
        mPresenter = presenter;
    }

    IDEFrame::~IDEFrame() {}
}
