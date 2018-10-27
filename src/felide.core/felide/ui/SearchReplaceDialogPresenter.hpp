
#ifndef __FELIDE_UI_SEARCHREPLACEDIALOG_PRESENTER_HPP__
#define __FELIDE_UI_SEARCHREPLACEDIALOG_PRESENTER_HPP__

#include <string>

namespace felide {
    class SearchReplaceDialog;
    class SearchReplaceDialogPresenter {
    public:
        SearchReplaceDialogPresenter();

        ~SearchReplaceDialogPresenter();

        void search(const std::string &search);

        void replace(const std::string &search, const std::string &replace);

        void replaceAll(const std::string &search, const std::string &replace);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
