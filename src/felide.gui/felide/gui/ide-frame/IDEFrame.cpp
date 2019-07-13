
#include "IDEFrame.hpp"

#include "IDEFramePresenter.hpp"

#include <felide/gui/Menu.hpp>

namespace felide {
    IDEFrame::IDEFrame(IDEFramePresenter *presenter) {
        m_presenter = presenter;
    }

    IDEFrame::~IDEFrame() {}
}
