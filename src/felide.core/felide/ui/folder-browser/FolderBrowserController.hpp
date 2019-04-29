
#ifndef __FELIDE_UI_FOLDERBROWSERCONTROLLER_HPP_
#define __FELIDE_UI_FOLDERBROWSERCONTROLLER_HPP_

#include <string>
#include <felide/Predef.hpp>
#include <boost/optional/optional_fwd.hpp>

namespace felide {
    class FELIDE_API IDEModel;
    class FELIDE_API FolderBrowser;
    class FELIDE_API DialogManager;
    class FELIDE_API IDEFrameController;

    class FELIDE_API FolderBrowserController {
    public:
        FolderBrowserController(IDEFrameController *ideFramePresenter);

        void attachView(FolderBrowser *folderBrowser, DialogManager *dialogManager);

        void detachView();

        virtual ~FolderBrowserController();

        virtual void onBrowseFolder();

        virtual void onCreateFile();

        virtual void onCreateFolder();

        virtual void onMoveSelectedPath(const std::string &targetFolder);

        virtual void onRenameSelectedPath();

        virtual void onOpenSelectedFile();

        virtual void onDeleteSelectedPath();

    private:
        boost::optional<std::string> askValidPath(const std::string &title, const std::string &prompt, const std::string &promptForInvalidInput, const std::string &defaultValue);

    private:
        IDEFrameController *ideFramePresenter;
        FolderBrowser *m_folderBrowser;
        DialogManager *m_dialogManager;
    };
} 

#endif
