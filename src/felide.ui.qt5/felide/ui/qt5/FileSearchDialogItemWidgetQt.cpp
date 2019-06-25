
#include "FileSearchDialogItemWidgetQt.hpp"

#include <QLabel>
#include <QHBoxLayout>

namespace felide {
    FileSearchDialogItemWidgetQt::FileSearchDialogItemWidgetQt(QWidget *parent, const QString &fileTitle, const QString &fileFolder) : QWidget(parent) {
        auto fileTitleLabel = new QLabel(fileTitle);
        auto filePathLabel = new QLabel(fileFolder);

        auto layout = new QHBoxLayout();

        layout->addWidget(fileTitleLabel);
        layout->addWidget(filePathLabel);

        this->setLayout(layout);
    }
}
