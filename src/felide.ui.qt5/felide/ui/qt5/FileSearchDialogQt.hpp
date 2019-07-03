
#ifndef __FELIDE_UI_QT5_FILESEARCHDIALOGQT_HPP__
#define __FELIDE_UI_QT5_FILESEARCHDIALOGQT_HPP__

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QDialogButtonBox>
#include <felide/ui/file-search-dialog/FileSearchDialog.hpp>
#include "DialogManagerQt.hpp"

namespace felide {
    class FileSearchDialogQt : public QDialog, public FileSearchDialog {
        Q_OBJECT

    public:
        explicit FileSearchDialogQt(QWidget *parent, FileSearchDialogPresenter *presenter);

        virtual ~FileSearchDialogQt();

        QString selectedFile() const;

    public:
        virtual void displayFileList(const std::vector<FileViewData> &files) override;

        virtual void hide() override;

        virtual void clearFileList() override;

    private:
        QLineEdit *filePatternLineEdit = nullptr;
        QListWidget *filesListWidget = nullptr;
        QDialogButtonBox *okCancelButtonBox = nullptr;
    };
}

#endif
