
#include "DialogManagerGtk.hpp"

namespace felide {
    DialogManagerGtk::DialogManagerGtk(Gtk::Window &parent_) : parent(parent_)  {}

    DialogManagerGtk::~DialogManagerGtk() {}

    static Gtk::MessageType mapMessageIcon(DialogIcon icon) {
        switch (icon) {
            case DialogIcon::Question:      return Gtk::MESSAGE_QUESTION; 
            case DialogIcon::Information:   return Gtk::MESSAGE_INFO; 
            case DialogIcon::Error:         return Gtk::MESSAGE_ERROR;
            case DialogIcon::Warning:       return Gtk::MESSAGE_WARNING;
            default:                        return Gtk::MESSAGE_OTHER;
        }
    }

    enum ButtonsGtk {
        FELIDE_GTK_CANCEL, 
        FELIDE_GTK_OK, 
        FELIDE_GTK_YES, 
        FELIDE_GTK_NO
    };

    static DialogButton mapResponseButton(ButtonsGtk result) {
        switch (result) {
            case FELIDE_GTK_CANCEL: return DialogButton::Cancel;
            case FELIDE_GTK_OK: return DialogButton::Ok;
            case FELIDE_GTK_YES: return DialogButton::Yes;
            case FELIDE_GTK_NO: return DialogButton::No;
            default: return DialogButton::Cancel;
        }
    }

    DialogButton DialogManagerGtk::showMessageDialog(const MessageDialogData &data) const {
        Gtk::MessageType messageIcon = mapMessageIcon(data.icon);
        
        auto dialog = Gtk::MessageDialog{
            parent, 
            data.title.c_str(),
            false /* use_markup */, 
            messageIcon,
            Gtk::BUTTONS_NONE
        };

        if (data.buttons & DialogButton::Ok) {
            dialog.add_button("_Ok", FELIDE_GTK_OK);
        }

        if (data.buttons & DialogButton::Yes) {
            dialog.add_button("_Yes", FELIDE_GTK_YES);
        }

        if (data.buttons & DialogButton::No) {
            dialog.add_button("_No", FELIDE_GTK_NO);
        }

        if (data.buttons & DialogButton::Cancel) {
            dialog.add_button("_Cancel", FELIDE_GTK_CANCEL);
        }

        const auto result = static_cast<ButtonsGtk>(dialog.run());

        return mapResponseButton(result);
    }

    boost::optional<std::string> DialogManagerGtk::showInputDialog(const InputDialogData &data) const {
        // TODO: Add implementation

        return {};
    }

    boost::optional<boost::filesystem::path> DialogManagerGtk::showFileDialog(const FileDialogData &data) const {
        // TODO: Add defaultPath usage

        const auto chooserAction = data.type == FileDialogType::OpenFile 
            ? Gtk::FILE_CHOOSER_ACTION_OPEN 
            : Gtk::FILE_CHOOSER_ACTION_SAVE;

        const auto acceptButtonCaption = data.type == FileDialogType::OpenFile 
            ? "_Open" : "_Save";

        Gtk::FileChooserDialog dialog(data.title.c_str(), chooserAction);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button(acceptButtonCaption, Gtk::RESPONSE_OK);
        dialog.set_transient_for(parent);

        for (auto filter : data.filters) {
            auto fileFilter = Gtk::FileFilter::create();
            fileFilter->set_name(filter.description.c_str());

            // TODO: Pass also the MIME Type
            fileFilter->add_mime_type("text/plain");
            dialog.add_filter(fileFilter);
        }

        if (int result = dialog.run(); result == Gtk::RESPONSE_OK) {
            const std::string path = dialog.get_filename();

            return boost::filesystem::path(path);
        }

        return {};
    }

    boost::optional<boost::filesystem::path> DialogManagerGtk::showFolderDialog(const FolderDialogData &data) {
        // TODO: Add defaultPath usage

        Gtk::FileChooserDialog dialog(data.title.c_str(), Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(parent);

        if (int result = dialog.run(); result == Gtk::RESPONSE_OK) {
            const std::string folderPath = dialog.get_filename();
            
            return boost::filesystem::path(folderPath);
        }

        return {};
    }

    boost::optional<boost::filesystem::path> DialogManagerGtk::showFileSearchDialog(const FileSearchDialogData &data) const {
        return {};
    }
}
