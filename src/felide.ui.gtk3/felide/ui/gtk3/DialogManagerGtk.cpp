
#include "DialogManagerGtk.hpp"

namespace felide {
    DialogManagerGtk::DialogManagerGtk(Gtk::Window &parent_) : parent(parent_)  {}

    DialogManagerGtk::~DialogManagerGtk() {}

    DialogButton DialogManagerGtk::showMessageDialog(const MessageDialogData &data) const {
        return DialogButton::Ok;
    }

    boost::optional<std::string> DialogManagerGtk::showInputDialog(const InputDialogData &data) const {
        return {};
    }

    boost::optional<boost::filesystem::path> DialogManagerGtk::showFileDialog(const FileDialogData &data) const {
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
        return {};
    }
}
