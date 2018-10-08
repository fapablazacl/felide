
#ifndef __FELIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__
#define __FELIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__

#include <felide/ui/DialogManager.hpp>
#include <QWidget>

namespace felide {
    class DialogManagerQt : public DialogManager {
    public:
        explicit DialogManagerQt(QWidget *parent);
        virtual ~DialogManagerQt();
        
        virtual DialogButton showMessageDialog(const std::string &title, const std::string &msg, const DialogIcon icon, const DialogButton buttons) const override;
		virtual boost::optional<std::string> showFileDialog(const FileDialogData& data) const override;
        virtual boost::optional<std::string> showFolderDialog(const std::string &title) override;

    private:
        QWidget *m_parent = nullptr;
    };
}

#endif
