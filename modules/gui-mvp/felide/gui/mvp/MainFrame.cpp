
#include "MainFrame.hpp"

#include <cassert>

namespace felide {
    MainFrame::View::View(MainFrame::Presenter *presenter) : presenter(presenter) {
        assert(presenter);
    }
}


namespace felide {
    MainFrame::Presenter::Presenter(MainFrame::Model *model) : model(model) {
        assert(model);
    }

    void MainFrame::Presenter::handleInitializedView(MainFrame::View *view) {
        assert(view);
        assert(model);

        view->displayTitle(model->getTitle());
        view->changeWindowState(MainFrame::W_FOLDERBROWSER, MainFrame::VS_HIDE);
        view->changeWindowState(MainFrame::W_OUTPUT, MainFrame::VS_SHOW);
        view->show();

        this->view = view;
    }

    MainFrame::CloseRequestAction MainFrame::Presenter::handleCloseRequest() {
        assert(view);
        assert(model);

        if (model->hasModifiedFiles()) {
            const std::string prompt = "Do you have modified files. Are you sure to want to exit?";

            if (view->askCloseConfirmation(model->getTitle(), prompt) == MainFrame::AR_OK) {
                return MainFrame::CRA_CLOSE;
            }

            return MainFrame::CRA_IGNORE;
        }

        return MainFrame::CRA_CLOSE;
    }
}
