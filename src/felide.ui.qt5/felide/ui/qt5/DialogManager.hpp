
#ifndef __FELIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__
#define __FELIDE_UI_DIALOGMANAGERVIEWIMPL_HPP__

#include "../DialogManagerView.hpp"
#include <QWidget>

namespace felide {
    class DialogManager : public DialogManagerView {
    public:
        explicit DialogManager(QWidget *parent);

        virtual ~DialogManager();
        virtual DialogButton showMessageDialog(const std::string &title, const std::string &msg, const DialogIcon icon, const DialogButton buttons) const override;
		virtual boost::optional<std::string> showFileDialog(const std::string &title, const FileDialogType dialogType, const std::vector<FileFilter> &filters) const override;

    private:
        QWidget *m_parent = nullptr;
    };
}

#endif
