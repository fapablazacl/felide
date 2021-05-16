
#pragma once

#include <map>
#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

#include <boost/optional.hpp>
#include <Xenoide/GUI/DocumentManager.hpp>

#include <Xenoide/GUI/Qt5/DialogManagerQt.hpp>
#include <Xenoide/GUI/Qt5/DocumentMdiSubWindowQt.hpp>

namespace Xenoide {
    class DocumentMdiSubWindowQt;
    class Document;
    class DocumentManagerMdiQt : public QWidget, public DocumentManager {
        Q_OBJECT

    public:
        explicit DocumentManagerMdiQt(QWidget *parent, DocumentManagerPresenter *presenter);

        virtual ~DocumentManagerMdiQt();
        
    public:
        boost::optional<int> getDocumentIndex(const DocumentMdiSubWindowQt *documentQt);
        
        void changeDocumentTitle(DocumentMdiSubWindowQt *documentQt, const std::string &title);
        
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
        DialogManagerQt mDialogManager;
    };
}
