
#include <Xenoide/GUI/mvp/DocumentManager.hpp>

#include <cassert>

namespace felide {
    DocumentManager::View::View(DocumentManager::Presenter *presenter) : presenter(presenter) {
        assert(presenter);
    }
}


namespace felide {
    DocumentManager::Presenter::Presenter(DocumentManager::Model *model) : model(model) {
        assert(model);
    }

    void DocumentManager::Presenter::handleInitializedView(DocumentManager::View *view) {
        assert(view);
        assert(model);

        // TODO: Perform view initialization

        this->view = view;
    }
}
