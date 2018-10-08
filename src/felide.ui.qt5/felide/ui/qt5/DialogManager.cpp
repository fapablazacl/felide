
#include "DialogManager.hpp"

#include <QMessageBox>
#include <QFileDialog>
#include <boost/algorithm/string/join.hpp>

namespace felide {
    DialogManager::DialogManager(QWidget *parent) {
        m_parent = parent;
    }

    DialogManager::~DialogManager() {}

    DialogButton DialogManager::showMessageDialog(const std::string &title, const std::string &msg, const DialogIcon icon, const DialogButton buttons) const {
        // Buttons
        QMessageBox::StandardButtons qbuttons;

        switch (buttons) {
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

        switch (icon) {
            case DialogIcon::Information:
                result = QMessageBox::information(m_parent, title.c_str(), msg.c_str(), qbuttons);
                break;
                
            case DialogIcon::Warning:
                result = QMessageBox::warning(m_parent, title.c_str(), msg.c_str(), qbuttons);
                break;

            case DialogIcon::Error:
                result = QMessageBox::critical(m_parent, title.c_str(), msg.c_str(), qbuttons);
                break;
                
            case DialogIcon::Question:
                result = QMessageBox::question(m_parent, title.c_str(), msg.c_str(), qbuttons);
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

    boost::optional<std::string> DialogManager::showFileDialog(const FileDialogData& data) const {
        const auto qfilters = mapFiltersToString(data.filters);

        QString filename;

        switch (data.type) {
            case FileDialogType::OpenFile:
                filename = QFileDialog::getOpenFileName (
                    m_parent,
                    data.title.c_str(),
                    QDir::currentPath(),
                    qfilters.c_str()
                );
                break;
            
            case FileDialogType::SaveFile:
                filename = QFileDialog::getSaveFileName (
                    m_parent,
                    data.title.c_str(),
                    QDir::currentPath(),
                    qfilters.c_str()
                );
                break;
        }

        if (filename.isNull()) {
            return {};
        }

        return filename.toStdString();
    }
    
    boost::optional<std::string> DialogManager::showFolderDialog(const std::string &title) {
        QFileDialog dialog;
        
        dialog.setWindowTitle(title.c_str());
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);
        
        if (dialog.exec()) {
            const QStringList folders = dialog.selectedFiles();
            
            assert(folders.size() == 1);
            const QString folder = folders[0];
            
            return folder.toStdString();
        } else {
            return {};
        }
    }
}
