
#ifndef __FELIDE_UI_DIALOGMANAGERGTK_HPP__
#define __FELIDE_UI_DIALOGMANAGERGTK_HPP__

#include <gtkmm.h>
#include <felide/ui/DialogManager.hpp>

namespace felide {
    class DialogManagerGtk : public DialogManager {
    public:
        DialogManagerGtk(Gtk::Window &parent);

        virtual ~DialogManagerGtk();

        virtual DialogButton showMessageDialog(const MessageDialogData &data) const override;

        virtual boost::optional<std::string> showInputDialog(const InputDialogData &data) const override;

        virtual boost::optional<boost::filesystem::path> showFileDialog(const FileDialogData &data) const override;

        virtual boost::optional<boost::filesystem::path> showFolderDialog(const FolderDialogData &data) override;

    private:
        Gtk::Window &parent;
    };
}

#endif
