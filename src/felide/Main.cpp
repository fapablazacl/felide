
#include <cassert>
#include <felide/Core.hpp>
#include <felide/ui/UIToolkit.hpp>
#include <felide/ui/MainWindowView.hpp>
#include <felide/ui/MainLoop.hpp>
#include <felide/system/PluginManager.hpp>

#include <iostream>

int main(int argc, char **argv) {
    felide::Core core;

    auto pluginManager = core.getPluginManager();
    pluginManager->loadPlugin("libfelide.ui.qt5.so");

    auto toolkit = core.getToolkit();
    assert(toolkit);

    return toolkit->runApp(argc, argv);

/*
    auto mainLoop = viewFactory->createMainLoop(argc, argv);
    assert(mainLoop);

    auto mainWindow = viewFactory->createMainWindow();
    assert(mainWindow);

    // mainWindow->show();

    return mainLoop->run();
    */
}

#if defined(_WINDOWS)

#include <Windows.h>
#include <cstdlib>
int CALLBACK  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void) hInstance;
    (void) hPrevInstance;
    (void) lpCmdLine;
    (void) nCmdShow;

    int argc = 0;
    
    LPWSTR* wargv = ::CommandLineToArgvW(GetCommandLineW(), &argc);
    char **argv = new char*[argc + 1];

    for (int i=0; i<argc; ++i) {
        argv[i] = new char[std::wcslen(wargv[i])];
        std::wcstombs(argv[i], wargv[i], 0);
    }
    LocalFree(wargv);

    argv[argc] = NULL;

    int exitCode = main(argc, argv);

    for (int i=0; i<argc; ++i) {
        delete[] argv[i];
    }

    delete[] argv;

    return exitCode;
}

#endif
