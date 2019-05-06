
#ifndef __FELIDE_UI_DOCUMENTPRESENTER_HPP__
#define __FELIDE_UI_DOCUMENTPRESENTER_HPP__

#include <string>

namespace felide {
    class Document;
    class DocumentModel;
    class FileDialogService;
    
    class DocumentPresenter {
    public:
        DocumentPresenter(DocumentModel *model);

        ~DocumentPresenter();

        void onInitialized(Document *view);

        void onContentChanged();

        void onTitleChanged();

        void onSave();

    private:
        std::string computeTitle(DocumentModel *model) const;

    private:
        Document *view = nullptr;
        DocumentModel *model = nullptr;
    };
}

#endif
