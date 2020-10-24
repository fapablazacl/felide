
#pragma once

#include <map>
#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

#include <boost/optional.hpp>
#include <felide/gui/document-manager/DocumentManager.hpp>

#include "DialogManagerQt.hpp"

namespace felide {
    class DocumentQt;
    class Document;
    class QMdiDocumentManager : public QWidget, public DocumentManager {
        Q_OBJECT

    public:
        explicit QMdiDocumentManager(QWidget *parent, DocumentManagerPresenter *presenter);

        virtual ~QMdiDocumentManager();
        
    public:
        boost::optional<int> getDocumentIndex(const DocumentQt *editor);
        
        void changeDocumentTitle(DocumentQt *editor, const std::string &title);
        
    public:
        Document* appendDocument(DocumentPresenter *documentPresenter) override;

        void setCurrentDocument(Document *document) override;

        Document* getCurrentDocument() override;

        std::size_t getDocumentCount() const override;

        Document* getDocument(const std::size_t index) override;
        
        void closeDocument(Document *document) override;

        void showDocument(Document *document) override;

    private:
        QMdiArea *mMdiArea = nullptr;
        DialogManagerQt dialogManager;
        std::map<DocumentQt*, QMdiSubWindow*> documentSubWindowMap;
    };
} 
