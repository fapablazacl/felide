
#ifndef __FELIDE_UI_FOLDERBROWSERPRESENTER_HPP_
#define __FELIDE_UI_FOLDERBROWSERPRESENTER_HPP_

#include <string>
#include <felide/Predef.hpp>

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

        virtual void createFile(const std::string &filePath);

        virtual void createFolder(const std::string &folderPath);

        virtual void renameCurrentPath();

        virtual void openCurrentFile();

        virtual void deleteCurrentPath();

    private:
        IDEFramePresenter *ideFramePresenter;
        FolderBrowser *m_folderBrowser;
        DialogManager *m_dialogManager;
    };
} 

#endif
