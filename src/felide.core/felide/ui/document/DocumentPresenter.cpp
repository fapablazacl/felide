
#include "DocumentPresenter.hpp"

#include "DocumentModel.hpp"
#include "Document.hpp"

#include <boost/filesystem/path.hpp>
#include <felide/util/FileService.hpp>

namespace felide {
    DocumentPresenter::DocumentPresenter(DocumentModel *model) {
        this->model = model;
    }

    DocumentPresenter::~DocumentPresenter() {}

    void DocumentPresenter::onInitialized(Document *view) {
        this->view = view;

        if (model->hasFilePath()) {
            auto fileService = FileService::create();
            auto content = fileService->load(model->getFilePath());

            model->setContent(content);
        }

        const std::string title = this->computeTitle(model);
        view->setTitle(title);
        view->setContent(model->getContent());
    }

    void DocumentPresenter::onContentChanged() {
        model->modify();

        const std::string title = this->computeTitle(model);
        view->setTitle(title);
    }

    void DocumentPresenter::onSave() {
        auto fileService = FileService::create();

        model->setContent(view->getContent());

        const std::string fileName = model->getFilePath();
        const std::string content = model->getContent();
        
        fileService->save(fileName, content);

        model->setFilePath(fileName);
        model->setModifiedFlag(false);

        const std::string title = this->computeTitle(model);

        view->setTitle(title);
    }

    void DocumentPresenter::onTitleChanged() {
        const std::string title = this->computeTitle(model);
        view->setTitle(title);
    }

    std::string DocumentPresenter::computeTitle(DocumentModel *model) const {
        std::string title;

        if (model->hasFilePath()) {
            title = boost::filesystem::path(model->getFilePath()).filename().string();
        } else {
            title = "Untitled " + std::to_string(model->getTag());
        }
        
        title = (model->getModifiedFlag() ? "[*]" : "") + title;

        return title;
    }

    void DocumentPresenter::onClose() {
        // TODO: Add implementation
    }

    void DocumentPresenter::onShow() {
        // TODO: Add implementation
    }

    bool DocumentPresenter::hasFilePath(const boost::filesystem::path &filePath) const {
        return boost::filesystem::path(model->getFilePath()) == filePath;
    }
    
    Document* DocumentPresenter::getView() const {
        return view;
    }

    DocumentModel* DocumentPresenter::getModel() const {
        return model;
    }
}
