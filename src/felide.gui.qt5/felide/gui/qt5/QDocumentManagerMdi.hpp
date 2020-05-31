
#pragma once

#include <QWidget>
#include <QTabWidget>

#include <boost/optional.hpp>
#include <felide/gui/document-manager/DocumentManager.hpp>

#include "DialogManagerQt.hpp"

namespace felide {
    class DocumentQt;
    class Document;
    class QDocumentManagerMdi : public QWidget, public DocumentManager {
        Q_OBJECT

    public:
        explicit QDocumentManagerMdi(QWidget *parent, DocumentManagerPresenter *presenter);

        virtual ~QDocumentManagerMdi();
        
    public:
        boost::optional<int> getDocumentIndex(const DocumentQt *editor);
        
        void changeDocumentTitle(DocumentQt *editor, const std::string &title);
        
    public:
        virtual Document* appendDocument(DocumentPresenter *documentPresenter) override;

        virtual void setCurrentDocument(Document *document) override;

        virtual Document* getCurrentDocument() override;

        virtual std::size_t getDocumentCount() const override;

        virtual Document* getDocument(const std::size_t index) override;
        
        virtual void closeDocument(Document *document) override;

        virtual void showDocument(Document *document) override;

    private:
        QTabWidget *m_tabWidget = nullptr;
        DialogManagerQt dialogManager;
    };
} 
