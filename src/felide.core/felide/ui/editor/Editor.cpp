
#include "Editor.hpp"

#include <felide/util/OS.hpp>

namespace felide {
    EditorConfig EditorConfig::Default() {
        switch (getCurrentOS()) {
            case OS::Linux: return {"Inconsolata", 8, 4, true, true};
            case OS::Windows: return {"Consolas", 8, 4, true, true};
            default: return {"Consolas", 12, 4, true, true};
        }
    }

    Editor::~Editor() {}
}
