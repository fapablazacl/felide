
#include <Xenoide/Gui/Document.hpp>

#include <Xenoide/Core/OS.hpp>

namespace Xenoide {
    DocumentConfig DocumentConfig::Default() {
        // TODO: Parametrize this parameters into an external file
        switch (getCurrentOS()) {
            case OS::Linux: return {"Monospace", 10, 4, true, true};
            case OS::Windows: return {"Consolas", 10, 4, true, true};
            default: return {"Consolas", 10, 4, true, true};
        }
    }

    Document::~Document() {}
}
