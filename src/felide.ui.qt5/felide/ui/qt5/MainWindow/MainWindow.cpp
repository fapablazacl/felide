
#include "MainWindow.hpp"

#include <vector>
#include <functional>
#include "MainWindowPresenter.hpp"

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
        presenter.attachView(this);

        this->setupMenuBar();

        m_tabbedEditorManager = new TabbedEditorManager(this);
        this->setCentralWidget(m_tabbedEditorManager);
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

    EditorManagerView* MainWindow::getEditorManagerView() {
        return m_tabbedEditorManager;
    }
}
