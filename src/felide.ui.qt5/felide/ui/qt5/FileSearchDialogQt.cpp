
#include "FileSearchDialogQt.hpp"

#include <iostream>
#include <QVBoxLayout>
#include <felide/ui/file-search-dialog/FileSearchDialogPresenter.hpp>

#include "FileSearchDialogItemWidgetQt.hpp"

namespace felide  {
    FileSearchDialogQt::FileSearchDialogQt(QWidget *parent, FileSearchDialogPresenter *presenter) : QDialog(parent), FileSearchDialog(presenter) {
        this->filePatternLineEdit = new QLineEdit();
        this->filesListWidget = new QListWidget();
        this->okCancelButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        QObject::connect(this->okCancelButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        QObject::connect(this->okCancelButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        auto layout = new QVBoxLayout();

        layout->addWidget(this->filePatternLineEdit);
        layout->addWidget(this->filesListWidget);
        layout->addWidget(this->okCancelButtonBox);

        this->setLayout(layout);

        QObject::connect(this->filePatternLineEdit, &QLineEdit::textEdited, [this](const QString &text) {
            this->presenter->onFilenameFilterRequested(text.toStdString());
        });

        this->presenter->onInitialized(this);
    }

    FileSearchDialogQt::~FileSearchDialogQt() {}

    QString FileSearchDialogQt::selectedFile() const {
        if (this->filesListWidget->currentItem()) {
            return this->filesListWidget->currentItem()->text();
        }

        return "";
    }

    void FileSearchDialogQt::displayFileList(const std::vector<FileSearchDialog::FileViewData> &files) {
        this->filesListWidget->clear();

        for (const FileSearchDialog::FileViewData &fileViewData : files) {
            auto fileItem = new QListWidgetItem();
            this->filesListWidget->addItem(fileItem);

            auto fileItemWidget = new FileSearchDialogItemWidgetQt(
                nullptr, 
                fileViewData.fileTitle.c_str(), 
                fileViewData.fileFolder.c_str()
            );

            this->filesListWidget->setItemWidget(fileItem, fileItemWidget);
        }
    }

    void FileSearchDialogQt::hide() {
        
    }
}
