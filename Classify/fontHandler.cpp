#include "stdafx.h"
#include "fontHandler.h"
int CALLBACK enumFontFamilyCallback(
    const LOGFONT    *lpelfe,
    const TEXTMETRIC *lpntme,
    DWORD      FontType,
    LPARAM     lParam
) {
    OutputDebugString(lpelfe->lfFaceName);
    OutputDebugString(_T("\n"));
    std::vector<LOGFONTW> *vec = reinterpret_cast<std::vector<LOGFONTW> *>(lParam);
    vec->push_back(*reinterpret_cast<const LOGFONTW *>(lpelfe));
    return 1;
}

BOOL CALLBACK SetChildWindowFont(
    _In_ HWND   hwnd,
    _In_ LPARAM lParam
) {
    SendMessage(hwnd, WM_SETFONT, static_cast<WPARAM>(lParam), MAKELPARAM(true, 0));
    return TRUE;
}