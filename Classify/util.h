#pragma once
#include "constant.h"
bool openFileDialog_BeforeVista(HWND window);
bool openFileDialog_VistaOrLater();
UINT_PTR CALLBACK FakeHook(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);