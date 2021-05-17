
#ifndef __XENOIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__
#define __XENOIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__

#include <Xenoide/Gui/DialogManager.hpp>
#include <QWidget>

namespace Xenoide {
    class DialogManagerQt : public DialogManager {
    public:
        explicit DialogManagerQt(QWidget *parent);
        virtual ~DialogManagerQt();
        
        virtual DialogButton showMessageDialog(const MessageDialogData &data) const override;
        virtual boost::optional<boost::filesystem::path> showFileDialog(const FileDialogData& data) const override;
        virtual boost::optional<boost::filesystem::path> showFolderDialog(const FolderDialogData &data) override;
        virtual boost::optional<std::string> showInputDialog(const InputDialogData &data) const override;
        virtual boost::optional<boost::filesystem::path> showFileSearchDialog(const FileSearchDialogData &data) const override;

    private:
        QWidget *m_parent = nullptr;
    };
}

#endif
