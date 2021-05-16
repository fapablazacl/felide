
#include <Xenoide/GUI/IDEFrame.hpp>
#include <Xenoide/GUI/IDEFramePresenter.hpp>

#include <Xenoide/GUI/Menu.hpp>

namespace felide {
    IDEFrame::IDEFrame(IDEFramePresenter *presenter) {
        mPresenter = presenter;
    }

    IDEFrame::~IDEFrame() {}
}
