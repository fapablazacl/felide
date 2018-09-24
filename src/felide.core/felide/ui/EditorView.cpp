
#include "EditorView.hpp"

namespace felide {
    EditorConfig EditorConfig::Default() {
        return {
            "Inconsolata", 12, 4, true, true
        };
    }

    EditorView::~EditorView() {}
}
