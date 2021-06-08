
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

#include <Xenoide/Core/FileService.hpp>

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


// static const ILexer5 *lexerC = nullptr;

constexpr COLORREF black = RGB(0, 0, 0);
constexpr COLORREF white = RGB(255, 255, 255);
constexpr char *defaultFontName = "Courier New";
constexpr int defaultFontSize = 10;

enum class CodeLanguage {
    TEXT,
    CPP,
    GLSL
};

static std::vector<std::string> extensionsC = {
    ".cpp", ".hpp", ".cxx", ".hxx", ".c++", ".h++", ".cc", ".hh", ".c", ".h"
};

static std::vector<std::string> extensionsGLSL = {
    ".vert", ".tesc", ".tese", ".geom", ".frag", ".comp", ".glsl"
};

CodeLanguage getCodeLanguage(const boost::filesystem::path &filePath) {
    if (filePath.has_extension()) {
        const auto ext = filePath.extension();

        for (const auto &extC : extensionsC) {
            if (ext == extC) {
                return CodeLanguage::CPP;
            }
        }

        for (const auto &extGLSL : extensionsGLSL) {
            if (ext == extGLSL) {
                return CodeLanguage::GLSL;
            }
        }
    }

    return CodeLanguage::TEXT;
}


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


static CodeViewLanguageConfig languageConfigGLSL = {
    { black, white, defaultFontSize, defaultFontName },
    // supported keywords
    "attribute const uniform varying "
    "layout "
    "centroid flat smooth noperspective "
    "patch sample "
    "break continue do for while switch case default "
    "if else "
    "subroutine "
    "in out inout "
    "float double int void bool true false "
    "invariant "
    "discard return "
    "mat2 mat3 mat4 dmat2 dmat3 dmat4 "
    "mat2x2 mat2x3 mat2x4 dmat2x2 dmat2x3 dmat2x4 "
    "mat3x2 mat3x3 mat3x4 dmat3x2 dmat3x3 dmat3x4 "
    "mat4x2 mat4x3 mat4x4 dmat4x2 dmat4x3 dmat4x4 "
    "vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 dvec2 dvec3 dvec4 "
    "uint uvec2 uvec3 uvec4 "
    "lowp mediump highp precision "
    "sampler1D sampler2D sampler3D samplerCube "
    "sampler1DShadow sampler2DShadow samplerCubeShadow "
    "sampler1DArray sampler2DArray "
    "sampler1DArrayShadow sampler2DArrayShadow "
    "isampler1D isampler2D isampler3D isamplerCube "
    "isampler1DArray isampler2DArray "
    "usampler1D usampler2D usampler3D usamplerCube "
    "usampler1DArray usampler2DArray "
    "sampler2DRect sampler2DRectShadow isampler2DRect usampler2DRect "
    "samplerBuffer isamplerBuffer usamplerBuffer "
    "sampler2DMS isampler2DMS usampler2DMS "
    "sampler2DMSArray isampler2DMSArray usampler2DMSArray "
    "samplerCubeArray samplerCubeArrayShadow isamplerCubeArray usamplerCubeArray "
    "struct "
        
    // The following are the keywords reserved for future use. Using them will result in an error:
    "common partition active "
    "asm "
    "class union enum typedef template this packed "
    "goto "
    "inline noinline volatile public static extern external interface "
    "long short half fixed unsigned superp "
    "input output "
    "hvec2 hvec3 hvec4 fvec2 fvec3 fvec4 "
    "sampler3DRect "
    "filter "
    "image1D image2D image3D imageCube "
    "iimage1D iimage2D iimage3D iimageCube "
    "uimage1D uimage2D uimage3D uimageCube "
    "image1DArray image2DArray "
    "iimage1DArray iimage2DArray uimage1DArray uimage2DArray "
    "image1DShadow image2DShadow "
    "image1DArrayShadow image2DArrayShadow "
    "imageBuffer iimageBuffer uimageBuffer "
    "sizeof cast "
    "namespace using "
    "row_major",
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

        // configure keywords, colors and fonts for GLSL
        // SetLanguage(lexerC, languageConfigGLSL);

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

        if (attribs.size > 0) {
            mWndScintilla.SendMessage(SCI_STYLESETSIZE, style, attribs.size);
        }
        
        if (attribs.face) {
            mWndScintilla.SendMessage(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(attribs.face));
        }
    }

    void ClearLanguage() {
        mWndScintilla.SendMessage(SCI_STYLECLEARALL);
        mWndScintilla.SendMessage(SCI_CLEARDOCUMENTSTYLE);
    }

    void SetLanguage(const ILexer5 *lexer, const CodeViewLanguageConfig &config) {
        mWndScintilla.SendMessage(SCI_STYLECLEARALL);
        mWndScintilla.SendMessage(SCI_CLEARDOCUMENTSTYLE);

        mWndScintilla.SendMessage(SCI_SETILEXER, 0, reinterpret_cast<LPARAM>(lexer));
        mWndScintilla.SendMessage(SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>(config.keywords.c_str()));

        SetStyleAttribs(SCE_C_DEFAULT, config.defaultStyle);
        for (const auto styleColor : config.stylesColors) {
            SetStyleAttribs(styleColor.first, {styleColor.second, white, 0, nullptr});
        }

        mWndScintilla.SendMessage(SCI_STYLESETBOLD, SCE_C_WORD, 1);
        mWndScintilla.SendMessage(SCI_STYLESETBOLD, SCE_C_WORD2, 1);
    }

    void SetInitialContent(const char *textContent) {
        mWndScintilla.SendMessage(SCI_SETTEXT, 0, reinterpret_cast<LPARAM>(textContent));
        mWndScintilla.SendMessage(SCI_EMPTYUNDOBUFFER);
        mWndScintilla.SendMessage(SCI_SETSAVEPOINT);
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
            auto dialog = CFileDialog{TRUE, _T("All Files\0*.*")};

            if (dialog.DoModal() != IDOK) {
                return;
            }

            const auto filePath = CString{dialog.m_szFileName};

            // load the file and put the content into the 
            const auto fileService = Xenoide::FileService::create();
            const auto fileContent = fileService->load(filePath.GetString());

            mCodeView.SetInitialContent(fileContent.c_str());

            // 
            const auto codeLang = getCodeLanguage(filePath.GetString());

            switch (codeLang) {
                case CodeLanguage::CPP: 
                    mCodeView.SetLanguage(Lexilla::MakeLexer("cpp"), languageConfigC); 
                    break;

                case CodeLanguage::GLSL: 
                    mCodeView.SetLanguage(Lexilla::MakeLexer("cpp"), languageConfigGLSL); 
                    break;

                default: 
                    mCodeView.ClearLanguage();
            }
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
