
#if defined(_WINDOWS)

extern int main(int argc, char **argv);

#include <Windows.h>
#include <cstdlib>
#include <cwchar>

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
