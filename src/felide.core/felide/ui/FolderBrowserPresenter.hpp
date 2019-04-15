
#ifndef __FELIDE_UI_FOLDERBROWSERPRESENTER_HPP_
#define __FELIDE_UI_FOLDERBROWSERPRESENTER_HPP_

#include <string>
#include <felide/Predef.hpp>
#include <boost/optional/optional_fwd.hpp>

namespace felide {
    class FELIDE_API IDEModel;
    class FELIDE_API FolderBrowser;
    class FELIDE_API DialogManager;
    class FELIDE_API IDEFramePresenter;

    class FELIDE_API FolderBrowserPresenter {
    public:
        FolderBrowserPresenter(IDEFramePresenter *ideFramePresenter);

        void attachView(FolderBrowser *folderBrowser, DialogManager *dialogManager);

        void detachView();

        virtual ~FolderBrowserPresenter();

        virtual void browseFolder();

        virtual void createFile();

        virtual void createFolder();

        virtual void renameSelectedPath();

        virtual void openSelectedFile();

        virtual void deleteSelectedPath();

    private:
        boost::optional<std::string> askValidPath(const std::string &title, const std::string &prompt, const std::string &promptForInvalidInput, const std::string &defaultValue);

    private:
        IDEFramePresenter *ideFramePresenter;
        FolderBrowser *m_folderBrowser;
        DialogManager *m_dialogManager;
    };
} 

#endif
