
#include <tuple>

#define STRICT
#define WIN32_LEAN_AND_MEAN
#define _WTL_USE_CSTRING

#include <atlbase.h>
#include <atlapp.h>

// WTL version of CComModule
extern CAppModule _Module;

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlmisc.h>
#include <atlcrack.h>
#include <atlsplit.h>
#include <atldlgs.h>

#include <Scintilla.h>
#include <Sci_Position.h>
#include <SciLexer.h>
#include <ILexer.h>
#include <Lexilla.h>

#include <vector>
#include <string_view>
#include "LexillaAccess.h"
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


class FolderView : public CWindowImpl<FolderView> {
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP_EX(FolderView)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
    END_MSG_MAP()

public:
    FolderView () {
        m_bMsgHandled = false;
    }

    LRESULT OnCreate(LPCREATESTRUCT cs) {
        SetMsgHandled(true);

        return 0;
    }

    void OnDestroy() {
        SetMsgHandled(false);
    }

    void DisplayFolder(CString folderPath) {

    }

private:
    
};


struct CodeViewStyleAttribs {
    COLORREF fore = RGB(255, 255, 255);
    COLORREF back = RGB(255, 255, 255);
    int size = 0;
    const char *face = nullptr;
};


static const ILexer5 *lexerC = nullptr;

constexpr COLORREF black = RGB(0, 0, 0);
constexpr COLORREF white = RGB(255, 255, 255);
constexpr char *defaultFontName = "Courier New";
constexpr int defaultFontSize = 10;

struct CodeViewLanguageConfig {
    CodeViewStyleAttribs defaultStyle = {
        black, white, defaultFontSize, defaultFontName
    };

    std::string keywords;
    std::vector<std::pair<int, COLORREF>> stylesColors;
};

static CodeViewLanguageConfig languageConfigC = {
    { black, white, defaultFontSize, defaultFontName },

    "alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept auto bitand bitor bool break case catch char "
	"char16_t char32_t class compl concept const constexpr const_cast continue decltype default delete do "
	"double dynamic_cast else enum explicit export extern false float for friend goto if inline int import long "
	"module mutable namespace new noexcept not not_eq nullptr operator or or_eq private protected public "
	"register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct "
	"switch synchronized template this thread_local "
	"throw true try typedef typeid typename union unsigned "
	"using virtual void volatile wchar_t while xor xor_eq",
    {
        {SCE_C_COMMENT, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_COMMENTLINE, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_COMMENTDOC, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_NUMBER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_WORD, RGB(0x00, 0x00, 0xFF)}, 
        {SCE_C_STRING, RGB(0x80, 0x00, 0x00)}, 
        {SCE_C_CHARACTER, RGB(0x80, 0x00, 0x00)}, 
        {SCE_C_UUID, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSOR, RGB(0xA0, 0x00, 0xFF)}, 
        {SCE_C_OPERATOR, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_IDENTIFIER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_STRINGEOL, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_VERBATIM, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_REGEX, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTLINEDOC, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_WORD2, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTDOCKEYWORD, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTDOCKEYWORDERROR, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_GLOBALCLASS, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_STRINGRAW, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_TRIPLEVERBATIM, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_HASHQUOTEDSTRING, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSORCOMMENT, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSORCOMMENTDOC, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_USERLITERAL, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_TASKMARKER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_ESCAPESEQUENCE, RGB(0x00, 0x00, 0x00)}
    }
};

class CodeView : public CWindowImpl<CodeView> {
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP_EX(CodeView)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SIZE(OnSize)
    END_MSG_MAP()

public:
    CodeView() {
        m_bMsgHandled = false;
    }

    LRESULT OnCreate(LPCREATESTRUCT cs) {
        mWndScintilla.Create(_T("Scintilla"), m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE);
        mWndScintilla.SendMessage(SCI_SETUSETABS, 0);
        mWndScintilla.SendMessage(SCI_SETTABWIDTH, 4);
        
        // configure for generic text
        SetStyleAttribs(STYLE_DEFAULT, {black, white, defaultFontSize, defaultFontName});

        // configure keywords, colors and fonts for C/C++
        SetLanguage(lexerC, languageConfigC);

        SetMsgHandled(true);

        return 0;
    }

    void OnDestroy() {
        mWndScintilla.DestroyWindow();
        mWndScintilla.Detach();

        SetMsgHandled(false);
    }

    void OnSize(UINT nType, CSize size) {
        const CRect rect = { 0, 0, size.cx, size.cy };

        mWndScintilla.SetWindowPos(NULL, rect, 0);
    }

    void SetStyleAttribs(const int style, const CodeViewStyleAttribs &attribs) {
        mWndScintilla.SendMessage(SCI_STYLESETFORE, style, attribs.fore);
        mWndScintilla.SendMessage(SCI_STYLESETBACK, style, attribs.back);

        if (attribs.size >= 1) {
            mWndScintilla.SendMessage(SCI_STYLESETSIZE, style, attribs.size);
        }
        
        if (attribs.face) {
            mWndScintilla.SendMessage(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(attribs.face));
        }
    }

    void SetLanguage(const ILexer5 *lexer, const CodeViewLanguageConfig &config) {
        mWndScintilla.SendMessage(SCI_STYLECLEARALL);

        mWndScintilla.SendMessage(SCI_SETILEXER, 0, reinterpret_cast<LPARAM>(lexer));
        mWndScintilla.SendMessage(SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>(config.keywords.c_str()));

        SetStyleAttribs(SCE_C_DEFAULT, config.defaultStyle);
        for (const auto styleColor : config.stylesColors) {
            SetStyleAttribs(styleColor.first, {styleColor.second, white, 0, nullptr});
        }

        mWndScintilla.SendMessage(SCI_STYLESETBOLD, SCE_C_WORD, 1);
        mWndScintilla.SendMessage(SCI_STYLESETBOLD, SCE_C_WORD2, 1);
    }

private:
    CWindow mWndScintilla;
    CFont mFntFixed;
};


// Frame Windows are defined with CFrameWindowImpl
class MainFrame :   public CFrameWindowImpl<MainFrame>,
                    public CUpdateUI<MainFrame>/*,
                    public CMessageFilter,
                    public CIdleHandler*/ {
public:
    DECLARE_FRAME_WND_CLASS("MainFrame", IDR_MAINFRAME)

    BEGIN_UPDATE_UI_MAP(MainFrame)
        // UPDATE_ELEMENT(ID_CLOCK_START, UPDUI_MENUPOPUP)
        // UPDATE_ELEMENT(ID_CLOCK_STOP, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(MainFrame)
        COMMAND_ID_HANDLER_EX(ID_FILE_NEW, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_OPEN, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_OPENFOLDER, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE_AS, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_EXIT, OnFileMenu)

        COMMAND_ID_HANDLER_EX(ID_EDIT_UNDO, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_REDO, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_CUT, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_COPY, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_PASTE, OnEditMenu)
        
        COMMAND_ID_HANDLER_EX(ID_HELP_ABOUT, OnAboutMenu)
        
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)

        CHAIN_MSG_MAP(CUpdateUI<MainFrame>)
        CHAIN_MSG_MAP(CFrameWindowImpl<MainFrame>)
    END_MSG_MAP()

public:
    LRESULT OnCreate(LPCREATESTRUCT cs) {
        const DWORD dwClientStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        const DWORD dwClientExStyle = WS_EX_CLIENTEDGE;

        m_hWndClient = mCodeView.Create(m_hWnd, rcDefault, NULL, dwClientStyle, dwClientExStyle);
        
        return 0;
    }

    void OnDestroy() {
        SetMsgHandled(false);
        PostQuitMessage(0);
    }

    void OnFileMenu(UINT uCode, int nID, HWND hwndCtrl) {
        if (nID == ID_FILE_OPEN) {
            
        }
        
        if (nID == ID_FILE_OPENFOLDER) {
            auto folderDialog = CFolderDialog(m_hWnd, _T("Open Folder"));

            if (folderDialog.DoModal() != IDOK) {
                return;
            }

            const CString folderPath =  folderDialog.GetFolderPath();
        }

        if (nID == ID_FILE_SAVE_AS) {
            int x = 0;
        }

        if (nID == ID_FILE_EXIT) {
            DestroyWindow();
        }
    }

    void OnEditMenu(UINT uCode, int nID, HWND hwndCtrl) {
        int x = 0;
    }

    void OnAboutMenu(UINT uCode, int nID, HWND hwndCtrl) {
        if (nID == ID_HELP_ABOUT) {
            AboutDlg dlg;
            dlg.DoModal();
        }
    }

private:
    CodeView mCodeView;
    CString mFolderPath;
};


CAppModule _Module;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    ::AtlInitCommonControls(ICC_COOL_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

    HMODULE hModScintilla = ::LoadLibrary(_T("Scintilla.dll"));

    if (hModScintilla == nullptr) {
        constexpr auto msg = _T("Required Scintilla.dll module wasn't found.");
        constexpr auto title = _T("XenoShader");

        ::MessageBox(nullptr, msg, title, MB_OK | MB_ICONERROR);
        return 1;
    }

    Lexilla::SetDefaultDirectory(".");
    Lexilla::Load(".");
    lexerC = Lexilla::MakeLexer("cpp");

    _Module.Init(NULL, hInstance);

    MainFrame mainFrame;
    MSG msg;

    if (NULL == mainFrame.CreateEx()) {
        return 1;
    }

    mainFrame.ShowWindow(nCmdShow);
    mainFrame.UpdateWindow();

    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    _Module.Term();

    ::FreeLibrary(hModScintilla);
    
    return static_cast<int>(msg.wParam);
}
