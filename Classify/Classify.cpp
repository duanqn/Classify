//Classify.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Classify.h"
#include "fontHandler.h"
#include "constant.h"
#include "../linux/gender.h"
#include "util.h"
#include <VersionHelpers.h>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    const WCHAR *title = _T("分班工具");
    wmemcpy_s(szTitle, MAX_LOADSTRING, title, wcslen(title));
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    OutputDebugString(szTitle);
    OutputDebugString(_T("\n"));
    LoadStringW(hInstance, IDC_CLASSIFY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLASSIFY));

    if (!IsWindows8OrGreater())
    {
        MessageBox(NULL, _T("You need at least Windows 8"), _T("Version Not Supported"), MB_OK);
        goto fail;
    }

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    OutputDebugString(_T("退出\n"));
fail:
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLASSIFY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLASSIFY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   HWND hButton = CreateWindowW(_T("BUTTON"), _T("选择配置文件"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 20, 20, 100, 40, hWnd, HMENU(ID_OPENFILE), hInstance, nullptr);

   SendMessage(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(nullptr), MAKELPARAM(0,0));
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HFONT currentFont = nullptr;
    LRESULT ret = 0xDEADBEEF;
    switch (message)
    {
    case WM_CREATE:
        {
            OutputDebugString(_T("WM_CREATE\n"));
            // set font of buttons
            HDC context = GetDC(hWnd);
            // Use pixel size
            SetMapMode(context, MM_TEXT);
            const int textPointSize = 10;
            int fontHeight = -MulDiv(textPointSize, GetDeviceCaps(context, LOGPIXELSY), 72);
            LOGFONTW logFont;
            logFont.lfCharSet = GB2312_CHARSET;
            logFont.lfFaceName[0] = L'\0';
            logFont.lfPitchAndFamily = 0;

            std::vector<LOGFONTW> allFonts;
            EnumFontFamiliesExW(context, &logFont, enumFontFamilyCallback, LPARAM(&allFonts), 0);
            LOGFONTW *ptrYaHei = nullptr;
            for (auto it = allFonts.begin(); it != allFonts.end(); ++it) {
                if (wcscmp(it->lfFaceName, L"微软雅黑") == 0) {
                    ptrYaHei = &(*it);
                    break;
                }
                else if (wcscmp(it->lfFaceName, L"Microsoft YaHei UI") == 0) {
                    ptrYaHei = &(*it);
                    break;
                }
            }
            if (ptrYaHei != nullptr) {
                ptrYaHei->lfHeight = fontHeight;
                ptrYaHei->lfWidth = 0;
                currentFont = CreateFontIndirectW(reinterpret_cast<LOGFONTW *>(ptrYaHei));
            }
            ret = DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_SETFONT:
        if (currentFont != nullptr) {
            bool dont_care = EnumChildWindows(
                hWnd,
                SetChildWindowFont,
                reinterpret_cast<LPARAM>(currentFont)
            );
        }
        ret = 0;
        break;
    case WM_COMMAND:
        {
            OutputDebugString(_T("WM_COMMAND\n"));
            int content = HIWORD(wParam);
            int from = LOWORD(wParam);
            // 分析菜单选择:
            switch (from) {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                ret = 0;
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                OutputDebugString(_T("Destroy window\n"));
                ret = 0;
                break;
            case ID_OPENFILE:
                OutputDebugString(_T("Button\n"));
                if (false) {
                    openFileDialog_VistaOrLater();
                }
                else{
                    OPENFILENAMEW fileInfo;
                    fileInfo.lStructSize = sizeof(fileInfo);
                    fileInfo.hwndOwner = hWnd;
                    fileInfo.hInstance = nullptr;
                    WCHAR filterBuffer[50];
                    memset(filterBuffer, 0, sizeof(filterBuffer));
                    const WCHAR *filter_1_0 = _T("All Files(*.*)\0");
                    const WCHAR *filter_1_1 = _T("*.*\0");
                    int pos = 0;
                    swprintf_s(filterBuffer + pos, sizeof(filterBuffer) / sizeof(filterBuffer[0]) - pos, filter_1_0);
                    pos += wcslen(filter_1_0);
                    filterBuffer[pos++] = _T('\0');
                    swprintf_s(filterBuffer + pos, sizeof(filterBuffer) / sizeof(filterBuffer[0]) - pos, filter_1_1);
                    pos += wcslen(filter_1_1);
                    filterBuffer[pos++] = _T('\0');
                    filterBuffer[pos++] = _T('\0');
                    fileInfo.lpstrFilter = filterBuffer;
                    fileInfo.lpstrCustomFilter = nullptr;
                    fileInfo.nMaxCustFilter = 0;
                    fileInfo.nFilterIndex = 1;
                    WCHAR fileBuffer[SIZE_MAXFILENAME];
                    memset(fileBuffer, 0, sizeof(fileBuffer));
                    fileInfo.lpstrFile = fileBuffer;
                    fileInfo.nMaxFile = sizeof(fileBuffer) / sizeof(fileBuffer[0]);
                    fileInfo.lpstrFileTitle = nullptr;
                    fileInfo.nMaxFileTitle = 0;
                    fileInfo.lpstrTitle = _T("打开文件");
                    fileInfo.lpstrInitialDir = _T(".");
                    fileInfo.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK;
                    fileInfo.lpTemplateName = nullptr;
                    fileInfo.lpfnHook = FakeHook;
                    fileInfo.lCustData = 0;
                    fileInfo.FlagsEx = 0;
                    fileInfo.lpstrDefExt = nullptr;

                    GetOpenFileNameW(&fileInfo);
                    OutputDebugString(fileInfo.lpstrFile);
                    OutputDebugString(_T("\n"));
                }
                ret = 0;
                break;
            default:
                ret = DefWindowProc(hWnd, message, wParam, lParam);
                break;
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            OutputDebugString(_T("WM_PAINT\n"));
            EndPaint(hWnd, &ps);
        }
        ret = 0;
        break;
    case WM_GETMINMAXINFO:
        {
            MINMAXINFO * info = reinterpret_cast<MINMAXINFO *>(lParam);
            info->ptMinTrackSize.x = 800;
            info->ptMinTrackSize.y = 600;
        }
        ret = 0;
        break;
    case WM_DESTROY:
        if (currentFont != nullptr) {
            DeleteObject(currentFont);
        }
        PostQuitMessage(0);
        ret = 0;
        break;
    default:
        ret = DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    assert(ret != 0xDEADBEEF);
    return ret;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
