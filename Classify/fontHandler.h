#pragma once
int CALLBACK enumFontFamilyCallback(
	const LOGFONT    *lpelfe,
	const TEXTMETRIC *lpntme,
	DWORD      FontType,
	LPARAM     lParam
);

BOOL CALLBACK SetChildWindowFont(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
);