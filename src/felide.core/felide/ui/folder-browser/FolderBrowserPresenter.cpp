
#include "FolderBrowserPresenter.hpp"

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <felide/ui/DialogManager.hpp>
#include <felide/ui/Menu.hpp>
#include <felide/ui/ide-frame/IDEFramePresenter.hpp>

#include "FolderBrowser.hpp"

namespace felide {
    static std::string describePathKind(const boost::filesystem::path &path) {
        if (boost::filesystem::is_directory(path)) {
            return "directory";
        } else {
            return "file";
        }
    }

    FolderBrowserPresenter::FolderBrowserPresenter(FolderBrowserModel *model, IDEFramePresenter *ideFramePresenter) {
        this->model = model;
        this->ideFramePresenter = ideFramePresenter;
    }

    FolderBrowserPresenter::~FolderBrowserPresenter() {}

    void FolderBrowserPresenter::onInitialized(FolderBrowser *folderBrowser, DialogManager *dialogManager) {
        this->view = folderBrowser;
        this->dialogView = dialogManager;
    }

    void FolderBrowserPresenter::onBrowseFolder() {
        if (auto folderPath = dialogView->showFolderDialog({"Open Folder", ""})) {
            view->displayFolder(folderPath.get().string());
        }
    }

    void FolderBrowserPresenter::onCreateFile() {
        const auto selectedPathOptional = view->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = boost::filesystem::path(*selectedPathOptional);

        // ask for the new filename
        const auto newFileName = this->askValidPath(
            "felide", 
            "Please, enter the new file name", 
            "Previous name was invalid. Enter the new file name", 
            "Newfile"
        );

        if (!newFileName) {
            return;
        }

        // construct the new file path
        boost::filesystem::path filePath;

        if (boost::filesystem::is_directory(selectedPath)) {
            filePath = selectedPath / newFileName.get();
        } else {
            filePath = selectedPath.parent_path() / newFileName.get();
        }

        // TODO: Replace logic with the FileService class
        // perform a "touch" function
        std::ofstream os;
        os.open(filePath.string().c_str(), std::ios_base::out);
        os.close();
    }

    void FolderBrowserPresenter::onCreateFolder() {
        // 
        const auto selectedPathOptional = view->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = boost::filesystem::path(*selectedPathOptional);

        // ask the new folder name
        const auto newFolderName = this->askValidPath(
            "felide", 
            "Please, enter the new folder name", 
            "Previous name was invalid. Enter the new folder name", 
            "Newfolder"
        );

        if (!newFolderName) {
            return;
        }

        // construct folder path
        boost::filesystem::path folderPath;

        if (boost::filesystem::is_directory(selectedPath)) {
            folderPath = selectedPath / newFolderName.get();
        } else {
            folderPath = selectedPath.parent_path() / newFolderName.get();
        }

        // create the directory on his final location
        namespace fs = boost::filesystem;
        boost::system::error_code errorCode;

        fs::create_directory(folderPath, errorCode);

        // TODO: Notify to the view the change in the filesystem (?)
    }

    void FolderBrowserPresenter::onOpenSelectedFile() {
        // determine the currently selected path
        if (const auto selectedPath = view->getSelectedPath()) {
            const auto filePath = boost::filesystem::path(selectedPath.get());

            if (!boost::filesystem::is_directory(filePath)) {
                ideFramePresenter->onFileOpen(filePath.string());
            } 
        }
    }

    void FolderBrowserPresenter::onMoveSelectedPath(const std::string &targetFolder) {
        // TODO: Add directory check to the targetFolder variable

        namespace fs = boost::filesystem;
        
        // determine the currently selected path
        const auto selectedPathOptional = view->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = fs::path(*selectedPathOptional);

        // compute destination path
        const auto destinationPath = fs::path(targetFolder) / selectedPath.filename();

        if (selectedPath == destinationPath) {
            return;
        }

        // existence check!
        if (fs::exists(destinationPath)) {
            auto messageDialog = MessageDialogData {};
            messageDialog.title = "felide";
            messageDialog.message = "File/Directory already exists. Replace it?";
            messageDialog.icon = DialogIcon::Warning;
            messageDialog.buttons = DialogButton::YesNo;

            const auto selectedButton = dialogView->showMessageDialog (messageDialog);

            if (selectedButton == DialogButton::No) {
                return;
            }
        }

        fs::rename(selectedPath, destinationPath);
    }

    void FolderBrowserPresenter::onRenameSelectedPath() {
        namespace fs = boost::filesystem;

        // determine the currently selected path
        const auto selectedPathOptional = view->getSelectedPath();
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

        if (!newFilenameOptional) {
            return;
        }

        // compute new path
        const auto newFilename = fs::path(*newFilenameOptional);
        const auto newPath = selectedPath.parent_path() / newFilename;

        if (boost::filesystem::exists(newPath)) {
            auto messageDialog = MessageDialogData {};
            messageDialog.title = "felide";
            messageDialog.message = "Another file already exists.";
            messageDialog.icon = DialogIcon::Error;
            messageDialog.buttons = DialogButton::Ok;

            dialogView->showMessageDialog(messageDialog);
            return;
        }

        // do the rename
        boost::filesystem::rename(selectedPath, newPath);
        
        // TODO: Notify to the view the change in the filesystem (?)
    }

    void FolderBrowserPresenter::onDeleteSelectedPath() {
        namespace fs = boost::filesystem;

        // determine the currently selected path
        const auto selectedPathOptional = view->getSelectedPath();
        if (!selectedPathOptional) {
            return;
        }

        const auto selectedPath = fs::path(*selectedPathOptional);
        
        // prompt the user confirmation
        auto messageDialog = MessageDialogData {};
        messageDialog.title = "felide";
        messageDialog.message = "Delete the \"" + selectedPath.filename().string() + "\" " + describePathKind(selectedPath) + "?";
        messageDialog.icon = DialogIcon::Warning;
        messageDialog.buttons = DialogButton::OkCancel;

        if (auto selectedButton = dialogView->showMessageDialog(messageDialog) == DialogButton::Cancel) {
            return;
        }
        
        // do the delete
        if (boost::filesystem::is_directory(selectedPath)) {
            boost::filesystem::remove_all(selectedPath);
        } else {
            boost::filesystem::remove(selectedPath);
        }

        // TODO: Notify to the view the change in the filesystem (?)
    }

    boost::optional<std::string> FolderBrowserPresenter::askValidPath(const std::string &title, const std::string &prompt, const std::string &promptForInvalidInput, const std::string &defaultValue) {
        int attemped = 0;

        boost::optional<std::string> validNamePath = {};

        while (true) {
            const std::string finalPrompt = (!attemped ? prompt : promptForInvalidInput);
            
            auto inputDialog = InputDialogData {};
            inputDialog.title = title;
            inputDialog.label = finalPrompt;
            inputDialog.defaultText = defaultValue;

            validNamePath = dialogView->showInputDialog(inputDialog);
            if (!validNamePath || boost::filesystem::native(*validNamePath)) {
                break;
            }

            ++attemped;
        }

        return validNamePath;
    }

    void FolderBrowserPresenter::onDisplayFolder(const boost::filesystem::path &folderPath) {
        view->displayFolder(folderPath.string());
    }

    void FolderBrowserPresenter::onContextMenuRequested(const Point &point) {
        const auto menu = Menu::menu("Context Menu", {
            Menu::action([this] () { this->onOpenSelectedFile(); }, "Open"),
            Menu::separator(),
            Menu::action([this] () { this->onCreateFile(); }, "Create File"),
            Menu::action([this] () { this->onCreateFolder(); }, "Create Folder"),
            Menu::separator(),
            Menu::action([this] () { this->onRenameSelectedPath(); }, "Rename"),
            Menu::action([this] () { this->onDeleteSelectedPath(); }, "Delete")
        });

        view->displayContextualMenu(point, menu);
    }
} 
