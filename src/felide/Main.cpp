
#include "view/win/CMainFrame.hpp"

CAppModule _Module;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	using felide::view::win::CMainFrame;

	_Module.Init(NULL, hInstance);

	CMainFrame mainFrame;
	MSG msg;

	if (NULL == mainFrame.Create(NULL, CWindow::rcDefault, _T("My First ATL Window!"))) {
		return 1;
	}

	mainFrame.ShowWindow(nCmdShow);
	mainFrame.UpdateWindow();

	while (::GetMessage(&msg, NULL, 0, 0) > 0) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	_Module.Term();

	return static_cast<int>(msg.wParam);
}
