
#include "FolderBrowserPresenter.hpp"

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

#include "FolderBrowser.hpp"
#include "DialogManager.hpp"
#include "IDEFramePresenter.hpp"

namespace felide {
    static std::string describePathKind(const boost::filesystem::path &path) {
        if (boost::filesystem::is_directory(path)) {
            return "directory";
        } else {
            return "file";
        }
    }

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

    void FolderBrowserPresenter::openSelectedFile() {
        // determine the currently selected path
        const auto selectedPathOptional = m_folderBrowser->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        ideFramePresenter->editorShow(*selectedPathOptional);
    }

    void FolderBrowserPresenter::renameSelectedPath() {
        // TODO: Notify to the other views
        namespace fs = boost::filesystem;

        // determine the currently selected path
        const auto selectedPathOptional = m_folderBrowser->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = fs::path(*selectedPathOptional);
        const auto pathKind = describePathKind(selectedPath);
        const auto prompt = "Please, enter a new name for the \"" + selectedPath.filename().string() + "\" " + pathKind;
        const auto prefix = "Invalid " + pathKind + " name. ";
        
        // prompt the user for a new path
        boost::optional<std::string> newFilenameOptional = this->askValidPath (
            "felide", prompt, prefix + prompt, selectedPath.filename().string()
        );

        if (newFilenameOptional) {
            const auto newFilename = fs::path(*newFilenameOptional);
            const auto newPath = selectedPath.parent_path() / newFilename;

            // do the rename
            boost::filesystem::rename(selectedPath, newPath);
        }
    }

    void FolderBrowserPresenter::deleteSelectedPath() {
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
            "Delete the \"" + selectedPath.filename().string() + "\" " + describePathKind(selectedPath) + "?", 
            DialogIcon::Warning, DialogButton::OkCancel
        );

        if (selectedButton == DialogButton::Cancel) {
            return;
        }
        
        // do the delete
        boost::filesystem::remove(selectedPath);
    }

    boost::optional<std::string> FolderBrowserPresenter::askValidPath(const std::string &title, const std::string &prompt, const std::string &promptForInvalidInput, const std::string &defaultValue) {
        int attemped = 0;

        boost::optional<std::string> validNamePath = {};

        while (true) {
            const std::string finalPrompt = (!attemped ? prompt : promptForInvalidInput);
            
            validNamePath = m_dialogManager->showInputDialog(title, finalPrompt, defaultValue);
            if (!validNamePath || boost::filesystem::native(*validNamePath)) {
                break;
            }

            ++attemped;
        }

        return validNamePath;
    }
} 
