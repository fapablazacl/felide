

#include "FolderBrowserPresenter.hpp"

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

#include "FolderBrowser.hpp"
#include "DialogManager.hpp"
#include "IDEFramePresenter.hpp"

namespace felide {
    FolderBrowserPresenter::FolderBrowserPresenter(IDEFramePresenter *ideFramePresenter) {
        this->ideFramePresenter = ideFramePresenter;
    }

    FolderBrowserPresenter::~FolderBrowserPresenter() {}

    void FolderBrowserPresenter::attachView(FolderBrowser *folderBrowser, DialogManager *dialogManager) {
        m_folderBrowser = folderBrowser;
        m_dialogManager = dialogManager;
    }

    void FolderBrowserPresenter::detachView() {
        m_folderBrowser = nullptr;
    }

    void FolderBrowserPresenter::browseFolder() {
        auto folderPathOptional = m_dialogManager->showFolderDialog("Open Folder");

        if (!folderPathOptional) {
            return;
        }

        m_folderBrowser->displayFolder(*folderPathOptional);
    }

    void FolderBrowserPresenter::createFile(const std::string &filePath) {
        std::ofstream os;
        os.open(filePath.c_str(), std::ios_base::out);
        os.close();
    }

    void FolderBrowserPresenter::createFolder(const std::string &folderPath) {
        namespace fs = boost::filesystem;
        boost::system::error_code errorCode;

        fs::create_directory(fs::path(folderPath), errorCode);
    }

    void FolderBrowserPresenter::openCurrentFile() {
        // determine the currently selected path
        const auto selectedPathOptional = m_folderBrowser->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        ideFramePresenter->editorShow(*selectedPathOptional);
    }

    void FolderBrowserPresenter::renameCurrentPath() {
        namespace fs = boost::filesystem;

        // determine the currently selected path
        const auto selectedPathOptional = m_folderBrowser->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = fs::path(*selectedPathOptional);
        
        // prompt the user for a new path
        const auto newFilenameOptional = m_dialogManager->showInputDialog("Please enter a New File Name", "New Name", selectedPath.filename().string());
        if (!newFilenameOptional) {
            return;
        }

        const auto newFilename = fs::path(*newFilenameOptional);
        const auto newPath = selectedPath.parent_path() / newFilename;

        // do the rename
        boost::filesystem::rename(selectedPath, newPath);

        // TODO: Notify to the corresponding entities
    }

    void FolderBrowserPresenter::deleteCurrentPath() {
        // TODO: Notify to the other views
        namespace fs = boost::filesystem;

        // determine the currently selected path
        const auto selectedPathOptional = m_folderBrowser->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = fs::path(*selectedPathOptional);
        
        // prompt the user confirmation
        auto selectedButton = m_dialogManager->showMessageDialog (
            "felide", 
            "Delete the file/directory" + selectedPath.filename().string() + "?", 
            DialogIcon::Warning, DialogButton::OkCancel
        );

        if (selectedButton == DialogButton::Cancel) {
            return;
        }
        
        // do the delete
        boost::filesystem::remove(selectedPath);

        // TODO: Notify to the corresponding entities
    }
} 
