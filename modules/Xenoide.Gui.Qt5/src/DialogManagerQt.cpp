
#include <Xenoide/Gui/Qt5/DialogManagerQt.hpp>

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <boost/algorithm/string/join.hpp>

#include <Xenoide/Gui/Qt5/FileSearchDialogQt.hpp>

#include <Xenoide/Gui/FileSearchDialog.hpp>

namespace Xenoide {
    DialogManagerQt::DialogManagerQt(QWidget *parent) {
        m_parent = parent;
    }

    DialogManagerQt::~DialogManagerQt() {}

    DialogButton DialogManagerQt::showMessageDialog(const MessageDialogData &data) const {
        // Buttons
        QMessageBox::StandardButtons qbuttons;

        switch (data.buttons) {
            case DialogButton::Ok: 
                qbuttons = QMessageBox::Ok;
                break;

            case DialogButton::OkCancel: 
                qbuttons = QMessageBox::Ok | QMessageBox::Cancel;
                break;
                
            case DialogButton::YesNo:
                qbuttons = QMessageBox::Yes |  QMessageBox::No;
                break;

            case DialogButton::YesNoCancel: 
                qbuttons = QMessageBox::Yes |  QMessageBox::No | QMessageBox::Cancel;
                break;

            default:
                // Unsupported flag combination
                assert(false);
        }
        
        // Icon
        int result = 0;

        switch (data.icon) {
            case DialogIcon::Information:
                result = QMessageBox::information(m_parent, data.title.c_str(), data.message.c_str(), qbuttons);
                break;
                
            case DialogIcon::Warning:
                result = QMessageBox::warning(m_parent, data.title.c_str(), data.message.c_str(), qbuttons);
                break;

            case DialogIcon::Error:
                result = QMessageBox::critical(m_parent, data.title.c_str(), data.message.c_str(), qbuttons);
                break;
                
            case DialogIcon::Question:
                result = QMessageBox::question(m_parent, data.title.c_str(), data.message.c_str(), qbuttons);
                break;
                
            default:
                // unsupported flag combination
                assert(false);
        }

        switch (result) {
            case QMessageBox::Ok: return DialogButton::Ok;
            case QMessageBox::Cancel: return DialogButton::Cancel;
            case QMessageBox::Yes: return DialogButton::Yes;
            case QMessageBox::No: return DialogButton::No;
            default: return DialogButton::YesNoCancel;
        }
    }

    static std::string mapFiltersToString(const std::vector<FileFilter> &dialogFilters) {
        std::vector<std::string> filters;

        for (auto &filter : dialogFilters) {
            std::string filterStr = filter.description;

            filterStr += " (";
            for (auto &wildcard : filter.wildcards) {
                filterStr += wildcard + " ";
            }

            filterStr += ") ";

            filters.push_back(filterStr);
        }

        const std::string filtersStr = boost::algorithm::join(filters, ";;");

        return filtersStr;
    }

    boost::optional<boost::filesystem::path> DialogManagerQt::showFileDialog(const FileDialogData& data) const {
        const auto qfilters = mapFiltersToString(data.filters);

        QString filename;

        switch (data.type) {
            case FileDialogType::OpenFile:
                filename = QFileDialog::getOpenFileName (
                    m_parent,
                    data.title.c_str(),
                    data.defaultPath.string().c_str(),
                    qfilters.c_str()
                );
                break;
            
            case FileDialogType::SaveFile:
                filename = QFileDialog::getSaveFileName (
                    m_parent,
                    data.title.c_str(),
                    data.defaultPath.string().c_str(),
                    qfilters.c_str()
                );
                break;
        }

        if (filename.isNull()) {
            return {};
        }

        return boost::filesystem::path(filename.toStdString());
    }
    
    boost::optional<boost::filesystem::path> DialogManagerQt::showFolderDialog(const FolderDialogData &data) {
        QFileDialog dialog;
        
        dialog.setWindowTitle(data.title.c_str());
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);
        
        if (dialog.exec()) {
            const QStringList folders = dialog.selectedFiles();
            
            assert(folders.size() == 1);
            const QString folder = folders[0];
            
            return boost::filesystem::path(folder.toStdString());
        } else {
            return {};
        }
    }

    boost::optional<std::string> DialogManagerQt::showInputDialog(const InputDialogData &data) const {
        bool ok = false;

        QString text = QInputDialog::getText (
            m_parent, 
            data.title.c_str(),
            data.label.c_str(), 
            QLineEdit::Normal,
            data.defaultText.c_str(), 
            &ok
        );

        if (ok) {
            return text.toStdString();
        } 
        
        return {};
    }

    boost::optional<boost::filesystem::path> DialogManagerQt::showFileSearchDialog(const FileSearchDialogData &data) const {
        auto fileSearchDialogModel = FileSearchDialog::Model::create(data.defaultPath);
        auto fileSearchDialogPresenter = FileSearchDialog::Presenter{fileSearchDialogModel.get()};
        auto fileSearchDialog = FileSearchDialogQt{m_parent, &fileSearchDialogPresenter};

        fileSearchDialog.setWindowTitle(data.title.c_str());
        
        if (fileSearchDialog.exec()) {
            const boost::filesystem::path selectedFilePath = fileSearchDialog.selectedFile().toStdString();

            return selectedFilePath;
        }

        return {};
    }
}
