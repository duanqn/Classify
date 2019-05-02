#include "stdafx.h"
#include "util.h"

bool openFileDialog_BeforeVista(HWND window) {
	OPENFILENAMEW fileInfo;
	fileInfo.lStructSize = sizeof(fileInfo);
	fileInfo.hwndOwner = window;
	fileInfo.hInstance = nullptr;
	WCHAR filterBuffer[50];
	memset(filterBuffer, 0, sizeof(filterBuffer));
	const WCHAR* filter_1_0 = _T("All Files(*.*)\0");
	const WCHAR* filter_1_1 = _T("*.*\0");
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
	fileInfo.lpstrTitle = _T("���ļ�");
	fileInfo.lpstrInitialDir = _T(".");
	fileInfo.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_EXPLORER;
	// Use these lines if you want the old style
	//fileInfo.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK;
	//fileInfo.lpfnHook = FakeHook;
	fileInfo.lpTemplateName = nullptr;
	fileInfo.lCustData = 0;
	fileInfo.FlagsEx = 0;
	fileInfo.lpstrDefExt = nullptr;

	GetOpenFileNameW(&fileInfo);
	OutputDebugString(fileInfo.lpstrFile);
	OutputDebugString(_T("\n"));
	
}
bool openFileDialog_VistaOrLater() {
	throw 1;
	return false;
}

UINT_PTR CALLBACK FakeHook(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	return 0;
}