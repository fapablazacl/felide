
#ifndef __FELIDE_UI_DOCUMENTPRESENTER_HPP__
#define __FELIDE_UI_DOCUMENTPRESENTER_HPP__

#include <string>
#include <boost/filesystem/path.hpp>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API Document;
    class FELIDE_API DocumentModel;
    class FELIDE_API DialogManager;

    class FELIDE_API DocumentPresenter {
    public:
        DocumentPresenter(DocumentModel *model);

        ~DocumentPresenter();

        void onInitialized(Document *view, DialogManager *dialogView);

        void onContentChanged();

        void onTitleChanged();

        void onSave();

        void onSaveAs();

        void onClose();

        void onShow();

        bool hasFilePath(const boost::filesystem::path &filePath) const;

        Document* getView() const;

        DocumentModel* getModel() const;

    private:
        std::string computeTitle(DocumentModel *model) const;

    private:
        DialogManager *dialogView = nullptr;
        Document *view = nullptr;
        DocumentModel *model = nullptr;
    };
}

#endif
