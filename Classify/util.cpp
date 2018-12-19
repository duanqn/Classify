#include "stdafx.h"
#include "util.h"
bool openFileDialog_BeforeVista() {
	return false;
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