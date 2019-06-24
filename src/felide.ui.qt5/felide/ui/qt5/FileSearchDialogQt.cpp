
#include "FileSearchDialogQt.hpp"

#include <iostream>
#include <QVBoxLayout>
#include <felide/ui/file-search-dialog/FileSearchDialogPresenter.hpp>

namespace felide  {
    FileSearchDialogQt::FileSearchDialogQt(QWidget *parent, FileSearchDialogPresenter *presenter) : QDialog(parent), FileSearchDialog(presenter) {
        this->filePatternLineEdit = new QLineEdit();
        this->filesListView = new QListView();
        this->okCancelButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        QObject::connect(this->okCancelButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        QObject::connect(this->okCancelButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        auto layout = new QVBoxLayout();

        layout->addWidget(this->filePatternLineEdit);
        layout->addWidget(this->filesListView);
        layout->addWidget(this->okCancelButtonBox);

        this->setLayout(layout);

        QObject::connect(this->filePatternLineEdit, &QLineEdit::textEdited, [this](const QString &text) {
            this->presenter->onFilenameFilterRequested(text.toStdString());
        });

        this->presenter->onInitialized(this);
    }

    FileSearchDialogQt::~FileSearchDialogQt() {}

    QString FileSearchDialogQt::selectedFile() const {
        return "";
    }

    void FileSearchDialogQt::displayFileList(const std::vector<std::string> &files) {
        std::cout << "Filtered " << files.size() << " files." << std::endl;
    }

    void FileSearchDialogQt::hide() {

    }
}
