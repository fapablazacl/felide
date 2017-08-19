
#include "CEditor.hpp"

namespace felide::view::win {
    LRESULT CEditor::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        m_edit.Create(m_hWnd);

        return 0;
    }
}
