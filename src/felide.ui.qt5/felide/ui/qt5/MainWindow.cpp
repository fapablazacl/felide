
#include "MainWindow.hpp"

#include <vector>
#include <functional>
#include <QMessageBox>
#include <QDesktopWidget>
#include <iostream>

#include "Editor.hpp"
#include "DialogManager.hpp"
#include "FolderBrowser.hpp"
#include <felide/ui/MainWindowPresenter.hpp>

namespace felide {
    static const std::map<Key, std::string> keyMap = {
        { Key::F1, "F1" },
        { Key::F2, "F2" },
        { Key::F3, "F3" },
        { Key::F4, "F4" },
        { Key::F5, "F5" },
        { Key::F6, "F6" },
        { Key::F7, "F7" },
        { Key::F8, "F8" },
        { Key::F9, "F9" },
        { Key::F10, "F10" },
        { Key::F11, "F11" },
        { Key::F12, "F12" },
        { Key::Q, "Q" },
        { Key::W, "W" },
        { Key::E, "E" },
        { Key::R, "R" },
        { Key::T, "T" },
        { Key::Y, "Y" },
        { Key::U, "U" },
        { Key::I, "I" },
        { Key::O, "O" },
        { Key::P, "P" },
        { Key::A, "A" },
        { Key::S, "S" },
        { Key::D, "D" },
        { Key::F, "F" },
        { Key::G, "G" },
        { Key::H, "H" },
        { Key::J, "J" },
        { Key::K, "K" },
        { Key::L, "L" },
        { Key::Z, "Z" },
        { Key::X, "X" },
        { Key::C, "C" },
        { Key::V, "V" },
        { Key::B, "B" },
        { Key::N, "N" },
        { Key::M, "M" }
    };

    static const std::map<Modifier, std::string> modifierMap = {
        { Modifier::Ctrl, "Ctrl" },
        { Modifier::Shift, "Shift" },
        { Modifier::Alt, "Alt" },
        { Modifier::CtrlShift, "Ctrl+Shift" },
        { Modifier::CtrlShiftAlt, "Ctrl+Shift+Alt" },
        { Modifier::ShiftAlt, "Shift+Alt" }
    };

    static QKeySequence mapShortcut(const Shortcut &shortcut) {
        if (shortcut.isNone()) {
            return QKeySequence();
        }

        const std::string key = keyMap.find(shortcut.key)->second;
        
        if (shortcut.modifier != Modifier::None) {
            const std::string modifier = modifierMap.find(shortcut.modifier)->second;

            return QKeySequence((modifier + "+" + key).c_str());
        } else {
            return QKeySequence(key.c_str());
        }
    }

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
                auto action = parentMenuPtr->addAction(menu.text.c_str(), nullptr, nullptr, mapShortcut(menu.shortcut));

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

    MainWindow::MainWindow(MainWindowPresenter *presenter) : MainWindowView(presenter) {
        this->setupMenuBar();
        this->setupEditorManager();
        this->setupDockUI();
        this->setupFolderBrowser();

        m_dialogManager = std::make_unique<DialogManager>(this);

        QDesktopWidget desktopWidget;
        
        const QRect screenSize = desktopWidget.availableGeometry(desktopWidget.primaryScreen());
        
        this->setMinimumSize(screenSize.size() * 0.4);
        this->resize(screenSize.size() * 0.7);

        m_presenter->attachView(this);
    }

    void MainWindow::setupMenuBar() {
        this->setMenuBar(createMenuBar(this, *m_menu));
    }

    void MainWindow::setupEditorManager() {
        m_editorManager = new EditorManager(this);

        connect(m_editorManager, &EditorManager::editorContentChanged, [&](Editor *editor) {
            assert(editor);
            m_presenter->editorContentModified(editor);
        });
        
        connect(m_editorManager, &EditorManager::editorCloseRequested, [&](Editor *editor) {
            assert(editor);
            m_presenter->editorCloseRequested(editor);
        });

        this->setCentralWidget(m_editorManager);
    }
    
    void MainWindow::setupDockUI() {
        const auto areas = QFlags<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        
        // setup folder browser dock widget
        m_folderBrowserDock = new QDockWidget("Folder Browser", this);
        
        m_folderBrowser = new FolderBrowser(m_folderBrowserDock);
        m_folderBrowserDock->setAllowedAreas(areas);
        m_folderBrowserDock->setWidget(m_folderBrowser);
        
        this->addDockWidget(Qt::LeftDockWidgetArea, m_folderBrowserDock);
    }
    
    void MainWindow::closeEvent(QCloseEvent *evt) {
        if (m_presenter->closeRequested()) {
            evt->accept();
        } else {
            evt->ignore();
        }
    }

    void MainWindow::setupFolderBrowser() {
        connect(m_folderBrowser, &FolderBrowser::projectItemOpenRequest, [&](const QString &filePath) {
            m_presenter->editorShow(filePath.toStdString());
        });
    }
}

namespace felide {
    EditorManagerView* MainWindow::getEditorManagerView() {
        return m_editorManager;
    }

    DialogManagerView* MainWindow::getDialogManagerView() {
        return m_dialogManager.get();
    }
    
    FolderBrowserView* MainWindow::getFolderBrowserView() {
        return m_folderBrowser;
    }
    
    void MainWindow::close() {
        QMainWindow::close();
    }

    void MainWindow::show() {
        QMainWindow::show();
    }
}
