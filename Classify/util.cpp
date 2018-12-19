#include "stdafx.h"
#include "util.h"
bool openFileDialog_BeforeVista() {
	return false;
}
bool openFileDialog_VistaOrLater() {
	throw 1;
	return false;
}