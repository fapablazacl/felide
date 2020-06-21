
#include "MainFrame.hpp"

#include <cassert>

namespace felide {
    MainFrame::Presenter::Presenter(MainFrame::Model *model) : model(model) {
        assert(model);
    }

    void MainFrame::Presenter::handleInitializedView(MainFrame::View *view) {
        assert(view);
        assert(model);

        view->changeTitle(model->getTitle());
        view->changeWindowState(MainFrame::W_FOLDERBROWSER, MainFrame::VS_HIDE);
        view->changeWindowState(MainFrame::W_OUTPUT, MainFrame::VS_SHOW);
        view->show();
    }

    void MainFrame::Presenter::handleCloseRequest() {
        assert(view);
        assert(model);

        if (model->hasModifiedFiles()) {
            if (view->askCloseConfirmation("XenoIde", "Do you have modified files. Are you sure to want to exit?")) {
                view->close();
            }
        }
    }
}
