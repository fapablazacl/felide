
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
                Menu::action([this] () { presenter.fileOpen(); }, "&Open"),
                Menu::action([this] () { presenter.fileSave(); }, "&Save"),
                Menu::action([this] () { presenter.fileSaveAs(); }, "Sa&ve As"),
                Menu::action([this] () { presenter.fileSaveAll(); }, "Save &All"),
                Menu::action([this] () { presenter.fileClose(); }, "&Close"),
                Menu::action([this] () { presenter.fileExit(); }, "&Exit")
            }),
            Menu::menu("&Edit", {
                Menu::action([] () {}, "&Undo"),
                Menu::action([] () {}, "&Redo"),
                Menu::action([] () {}, "&Cut"),
                Menu::action([] () {}, "C&opy"),
                Menu::action([] () {}, "&Paste")
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
    std::optional<std::string> MainWindow::openFileDialog(const FileDialogViewData &fileDialogData) {
        std::vector<std::string> filters;

        for (auto &filter : fileDialogData.filters) {
            std::string filterStr = filter.description;

            filterStr += " (";
            for (auto &wildcard : filter.wildcards) {
                filterStr += wildcard + " ";
            }

            filterStr += ") ";

            filters.push_back(filterStr);
        }

        const std::string filtersStr = felide::join(filters, ";;");

        QString filename =  QFileDialog::getOpenFileName (
          this,
          fileDialogData.title.c_str(),
          QDir::currentPath(),
          filtersStr.c_str()
        );

        if (filename.isNull()) {
            return {};
        }

        return filename.toStdString();
    }

    std::optional<std::string> MainWindow::saveFileDialog(const FileDialogViewData &fileDialogData) {
        return nullptr;
    }

    EditorManagerView* MainWindow::getEditorManagerView() {
        return m_tabbedEditorManager;
    }
}
