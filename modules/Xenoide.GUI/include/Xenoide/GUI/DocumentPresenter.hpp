
#ifndef __FELIDE_UI_DOCUMENTPRESENTER_HPP__
#define __FELIDE_UI_DOCUMENTPRESENTER_HPP__

#include <string>
#include <boost/filesystem/path.hpp>
#include <Xenoide/Core/Predef.hpp>

namespace felide {
    class Document;
    class DocumentModel;
    class DialogManager;

    class DocumentPresenter {
    public:
        enum class UserResponse {
            Cancel,
            Accept
        };

        DocumentPresenter(DocumentModel *model);

        ~DocumentPresenter();

        void onInitialized(Document *view, DialogManager *dialogView);

        void onContentChanged();

        void onTitleChanged();

        UserResponse onSave();

        UserResponse onSaveAs();

        UserResponse onCloseRequested();

        bool hasFilePath(const boost::filesystem::path &filePath) const;

        Document* getView() const;

        DocumentModel* getModel() const;

    private:
        std::string computeFileTitle(DocumentModel *model) const;

        std::string computeTitle(DocumentModel *model) const;

    private:
        DialogManager *dialogView = nullptr;
        Document *view = nullptr;
        DocumentModel *model = nullptr;
    };
}

#endif
