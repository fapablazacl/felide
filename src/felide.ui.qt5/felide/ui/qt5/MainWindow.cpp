
#include "MainWindow.hpp"

#include <vector>
#include <functional>
#include <QMessageBox>

#include "Editor.hpp"
#include "../MainWindowPresenter.hpp"

namespace felide {
    static void setupMenu(QMenu *parentMenuPtr, const Menu &menu) {
        switch (menu.kind) {
            case MenuKind::SubMenu: {
                QMenu *menuPtr = parentMenuPtr->addMenu(menu.text.c_str());

                for (const Menu &childMenu : menu.childs) {
                    setupMenu(menuPtr, childMenu);
                }

                break;
            }

            case MenuKind::Action: {
                auto action = parentMenuPtr->addAction(menu.text.c_str(), nullptr, nullptr, QKeySequence(menu.shortcut.c_str()));

                if (menu.callback) {
                    QObject::connect(action, &QAction::triggered, menu.callback);
                }

                break;
            }

            case MenuKind::Separator: {
                parentMenuPtr->addSeparator();
                break;
            }
        }
    }

    static QMenuBar* createMenuBar(QWidget *parent, const Menu &menuBar) {
        auto menuBarPtr = new QMenuBar(parent);

        for (const Menu &menu : menuBar.childs) {
            QMenu *menuPtr = menuBarPtr->addMenu(menu.text.c_str());

            for (const Menu &childMenu : menu.childs) {
                setupMenu(menuPtr, childMenu);
            }
        }

        return menuBarPtr;
    }

    MainWindow::MainWindow() {
        this->setupMenuBar();
        this->setupEditorManager();

        presenter.attachView(this);
    }

    void MainWindow::setupMenuBar() {
        auto mainMenu = Menu::menuBar({
            Menu::menu("&File", {
                Menu::action([this] () { presenter.fileNew(); }, "&New", "Ctrl+N"),
                Menu::action([this] () { presenter.fileOpen(); }, "&Open", "Ctrl+O"),
                Menu::action([this] () { presenter.fileSave(); }, "&Save", "Ctrl+S"),
                Menu::action([this] () { presenter.fileSaveAs(); }, "Sa&ve As"),
                Menu::action([this] () { presenter.fileSaveAll(); }, "Save &All"),
                Menu::action([this] () { presenter.fileClose(); }, "&Close"),
                Menu::action([this] () { presenter.fileExit(); }, "&Exit", "Alt+F4")
            }),
            Menu::menu("&Edit", {
                Menu::action([] () {}, "&Undo", "Ctrl+Z"),
                Menu::action([] () {}, "&Redo"),
                Menu::action([] () {}, "&Cut", "Ctrl+X"),
                Menu::action([] () {}, "C&opy", "Ctrl+C"),
                Menu::action([] () {}, "&Paste", "Ctrl+V")
            }),
            Menu::menu("&View", {
                Menu::action([] () {}, "&Output"), 
                Menu::action([] () {}, "&Workspace")
            }),
            Menu::menu("&Build", {
                Menu::action([] () {}, "&Clean"),
                Menu::action([] () {}, "&Execute")
            }),
            Menu::menu("&Help", {
                Menu::action([] () {}, "&About", "F1")
            }),
        });

        this->setMenuBar(createMenuBar(this, mainMenu));
    }

    void MainWindow::setupEditorManager() {
        m_tabbedEditorManager = new EditorManager(this);

        connect(m_tabbedEditorManager, &EditorManager::editorContentChanged, [&](Editor *editor) {
            assert(editor);
            presenter.editorContentModified(editor);
        });
        
        connect(m_tabbedEditorManager, &EditorManager::editorCloseRequested, [&](Editor *editor) {
            assert(editor);
            presenter.editorCloseRequested(editor);
        });

        this->setCentralWidget(m_tabbedEditorManager);
    }
}


#include <QFileDialog>
#include <felide/util/Strings.hpp>

namespace felide {

    static std::string mapFiltersToString(const std::vector<DialogViewData::FileFilter> &dialogFilters) {
        std::vector<std::string> filters;

        for (auto &filter : dialogFilters) {
            std::string filterStr = filter.description;

            filterStr += " (";
            for (auto &wildcard : filter.wildcards) {
                filterStr += wildcard + " ";
            }

            filterStr += ") ";

            filters.push_back(filterStr);
        }

        const std::string filtersStr = felide::join(filters, ";;");

        return filtersStr;
    }

    boost::optional<std::string> MainWindow::showDialogModal(const DialogViewData &dialogViewData) {
        const auto filters = mapFiltersToString(dialogViewData.filters);

        QString filename;

        switch (dialogViewData.dialogType) {
            case DialogType::OpenFile:
                filename = QFileDialog::getOpenFileName (
                    this,
                    dialogViewData.title.c_str(),
                    QDir::currentPath(),
                    filters.c_str()
                );
                break;
            
            case DialogType::SaveFile:
                filename = QFileDialog::getSaveFileName (
                    this,
                    dialogViewData.title.c_str(),
                    QDir::currentPath(),
                    filters.c_str()
                );
                break;
        }

        if (filename.isNull()) {
            return {};
        }

        return filename.toStdString();
    }
    
    boost::optional<bool> MainWindow::showAskModal(const std::string &title, const std::string &message) {
        const auto buttons = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
        const auto result = QMessageBox::question(this, title.c_str(), message.c_str(), buttons);
        
        switch (result) {
            case QMessageBox::Yes: return true;
            case QMessageBox::No: return false;
            case QMessageBox::Cancel: return {};
            default: return {};
        }
    }

    EditorManagerView* MainWindow::getEditorManagerView() {
        return m_tabbedEditorManager;
    }
}
