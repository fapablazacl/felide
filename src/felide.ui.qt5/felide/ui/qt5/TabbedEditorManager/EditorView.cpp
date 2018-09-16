
#include "EditorView.hpp"

namespace felide {
    EditorConfig EditorConfig::Default() {
        return {
            "monospace", 10, 4, true
        };
    }

    EditorView::~EditorView() {}
}
