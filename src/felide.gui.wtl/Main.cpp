
#include <felide/gui/ide-frame/IDEFrameModel.hpp>
#include <felide/gui/ide-frame/IDEFramePresenter.hpp>
#include "felide/gui/wtl/CIdeFrame.hpp"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

CAppModule _Module;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    using felide::CIdeFrame;
    using felide::IDEFramePresenter;
    using felide::IDEFrameModel;
    
    ::CoInitialize(NULL);

    AtlInitCommonControls(ICC_COOL_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

    _Module.Init(NULL, hInstance);

    auto ideFrameModel = IDEFrameModel::create();

    IDEFramePresenter ideFramePresenter{ideFrameModel.get()};
    CIdeFrame mainFrame{&ideFramePresenter};
    MSG msg;

    if (NULL == mainFrame.Create(NULL, CWindow::rcDefault, _T("felide"))) {
        return 1;
    }

    mainFrame.ShowWindow(nCmdShow);
    mainFrame.UpdateWindow();

    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    _Module.Term();

    ::CoUninitialize();

    return static_cast<int>(msg.wParam);
}
