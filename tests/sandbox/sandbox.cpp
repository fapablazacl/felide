//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//#include <Xenoide/core/TreeNode.hpp>
//#include <Xenoide/core/pom/Project.hpp>
//#include <Xenoide/core/pom/ModuleTarget.hpp>
//#include <Xenoide/core/pom/ModuleTargetType.hpp>
//#include <Xenoide/core/pom/TargetAction.hpp>
//
//#include <Xenoide/core/tasks/Task.hpp>
//#include <Xenoide/core/tasks/TaskNodeVisitor.hpp>
//
//#include <Xenoide/core/cpp/ModuleCompiler.hpp>
//#include <Xenoide/core/cpp/ModuleLinker.hpp>
//#include <Xenoide/core/cpp/ModuleToolset.hpp>
//
//#include <Xenoide/core/FileTypeRegistry.hpp>
//
//#define XSTR(a) STR(a)
//#define STR(a) #a
//
//static std::unique_ptr<Xenoide::Project> createProject(Xenoide::Toolset *toolset) {
//    const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);
//
//    std::cout << "Building project at \"" << rootPath << "\" ..." << std::endl;
//
//    auto project = Xenoide::Project::create("Xenoide", rootPath);
//
//    project->createTarget<Xenoide::ModuleTarget>()
//        ->setType(Xenoide::ModuleTargetType::Library)
//        ->setName("Xenoide.core")
//        ->setPath("src/Xenoide.core")
//        ->setToolset(toolset);
//
//    project->createTarget<Xenoide::ModuleTarget>()
//        ->setType(Xenoide::ModuleTargetType::Program)
//        ->setName("sandbox")
//        ->setPath("src/sandbox")
//        ->setToolset(toolset);
//
//    return project;
//}
//
//int main(int argc, char **argv) {
//    try {
//        const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);
//
//        const Xenoide::ActionContext context = {
//            {"${IncludeDirectory}", rootPath + "/src/Xenoide.core"},
//            {"${LinkLibraries}", "-lstdc++ -lstdc++fs"}
//        };
//
//        auto toolset = Xenoide::ModuleToolset::create (
//            ".Xenoide/build/gcc",
//            {
//                Xenoide::CompilerDescription {
//                    "gcc -std=c++17 -g -O0 -c ${InputFile} -o ${OutputFile} ${IncludeDirectory}",
//                    {".cpp", ".cxx", ".cc", ".c++"}, 
//                    ".obj",
//                    "/usr/local/Cellar/gcc/8.1.0/bin/",
//                    {
//                        {"${IncludeDirectory}", "-I"}
//                    }
//                }
//            }, {
//                Xenoide::LinkerDescription {
//                    "gcc ${ObjectFiles} -o ${TargetName} ${LinkLibraries}",
//                    "", 
//                    ""
//                }
//            }
//        );
//        std::cout << "Configured a default Toolset" << std::endl;
//
//        auto project = createProject(toolset.get());
//        std::cout << "Created a Project" << std::endl;
//
//        auto taskNode = project->createTask(Xenoide::TargetAction::Build, context);
//        std::cout << "Created a Build Task" << std::endl;
//
//        auto visitor = Xenoide::TaskNodeVisitor::create();
//
//        visitor->visit(taskNode.get(), [](Xenoide::Task *task) {
//            if (task) {
//                std::cout << task->toString() << std::endl;
//                task->perform();
//            } 
//        });
//
//        return 0;
//    } catch (const std::exception &exp) {
//        std::cout << exp.what() << std::endl;
//
//        return 1;
//    }
//
//    return 1001;
//}


#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <atlbase.h>
#include <atlwin.h>

#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlcrack.h>
#include <atlsplit.h>

#include "resource.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


// All Dialogs must inherit from the CDialogImpl template class.
// Must declar a class-scoped member IDD, wich haves the dialog's resource identifier.
class AboutDlg : public CDialogImpl<AboutDlg> {
public:
    enum {IDD = IDD_ABOUT};

public:
    BEGIN_MSG_MAP(AboutDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        COMMAND_ID_HANDLER(IDOK, OnOKCancel)
        COMMAND_ID_HANDLER(IDCANCEL, OnOKCancel)
    END_MSG_MAP()

public:
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        CenterWindow();

        // let the system set the focus
        return TRUE;
    }
 
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        EndDialog(IDCANCEL);
        return 0;
    }
 
    LRESULT OnOKCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        EndDialog(wID);
        return 0;
    }
};


template<typename T, COLORREF crColorBrush>
class PaintBackground {
public:
    BEGIN_MSG_MAP(PaintBackground)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    END_MSG_MAP()

public:
    PaintBackground() {
        m_hbrBackground = ::CreateSolidBrush(crColorBrush);
    }

    ~PaintBackground() {
        ::DeleteObject(m_hbrBackground);
    }

    LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        const T* pT = static_cast<T*>(this);
        HDC hDC = reinterpret_cast<HDC>(wParam);

        RECT rc;
        pT->GetClientRect(&rc);

        FillRect(hDC, &rc, m_hbrBackground);

        // Let know that we painted the background
        return 1;
    }

protected:
    HBRUSH m_hbrBackground = nullptr;
};


// using MainWindowTraits = CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, WS_EX_APPWINDOW>;
using MainWindowTraits = CFrameWinTraits;

// CWindow: Interface. Doesn't own any handle
// CWindowImpl: Implementation.
// MainWindowTraits: Traits for a Top-Level Window (MainWindow in this case)
class MainWindow :  public CWindowImpl<MainWindow, CWindow, MainWindowTraits>, 
                    public PaintBackground<MainWindow, RGB(0, 0, 255)> {

public:
    // MESSAGE_HANDLER: Maps a Window Message with a specific method
    // CHAIN_MSG_MAP: Chains the main message map with the one of the specified base class

public:
    using PaintBackgroundBase = PaintBackground<MainWindow, RGB(0, 0, 255)>;

public:
    DECLARE_WND_CLASS(_T("MainWindow"))

    BEGIN_MSG_MAP(MainWindow)
        COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnAbout)
        COMMAND_ID_HANDLER(ID_FILE_EXIT, OnFileExit);

        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

        CHAIN_MSG_MAP(PaintBackgroundBase)
    END_MSG_MAP()

public:
    LRESULT OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        DestroyWindow();
        return 0;
    }

    LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        AboutDlg dlg;
        dlg.DoModal();

        return 0;
    }

public:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled) {
        HMENU hMenu = LoadMenu(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDR_MENU1));

        SetMenu(hMenu);
        
        return 0L;
    }

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled) {
        DestroyWindow();
        return 0L;
    }

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        PostQuitMessage(0);
        return 0;
    }
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    ::AtlInitCommonControls(ICC_COOL_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

    MainWindow mainWindow;

    MSG msg;

    if (NULL == mainWindow.Create(NULL, CWindow::rcDefault, _T("Xenoide"))) {
        return 1;
    }

    mainWindow.ShowWindow(nCmdShow);
    mainWindow.UpdateWindow();

    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
