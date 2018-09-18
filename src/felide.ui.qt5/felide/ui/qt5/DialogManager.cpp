
#include "DialogManager.hpp"

#include <felide/util/Strings.hpp>
#include <QMessageBox>
#include <QFileDialog>


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
                qbuttons = QMessageBox::Ok: 
                break;

            case DialogButton::OkCancel: 
                qbuttons = QMessageBox::Ok | QMessageBox::Cancel: 
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
            default: assert(false);
        }
    }

    static std::string mapFiltersToString(const std::vector<DialogViewData::FileFilter> &dialogFilters) {
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

        const std::string filtersStr = felide::join(filters, ";;");

        return filtersStr;
    }

    boost::optional<std::string> DialogManager::showFileDialog(const std::string &title, const FileDialogType dialogType, const std::vector<FileFilter> &filters) const {
        const auto filters = mapFiltersToString(dialogViewData.filters);

        QString filename;

        switch (dialogViewData.dialogType) {
            case DialogType::OpenFile:
                filename = QFileDialog::getOpenFileName (
                    this,
                    dialogViewData.title.c_str(),
                    QDir::currentPath(),
                    filters.c_str()
                );
                break;
            
            case DialogType::SaveFile:
                filename = QFileDialog::getSaveFileName (
                    this,
                    dialogViewData.title.c_str(),
                    QDir::currentPath(),
                    filters.c_str()
                );
                break;
        }

        if (filename.isNull()) {
            return {};
        }

        return filename.toStdString();
    }
}
