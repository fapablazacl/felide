
#include "SearchReplaceDialogPresenter.hpp"

namespace felide {
    struct SearchReplaceDialogPresenter::Private {
        
    };

    SearchReplaceDialogPresenter::SearchReplaceDialogPresenter() {
        m_impl = new SearchReplaceDialogPresenter::Private();
    }

    SearchReplaceDialogPresenter::~SearchReplaceDialogPresenter() {
        delete m_impl;
    }

    void search(const std::string &search) {

    }

    void replace(const std::string &search, const std::string &replace) {

    }

    void replaceAll(const std::string &search, const std::string &replace) {

    }
}
