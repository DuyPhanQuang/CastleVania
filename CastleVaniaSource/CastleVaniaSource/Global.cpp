#include "Global.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>

using namespace std;

int currentFormGlobal;
int nextFormGlobal;

bool isInitedDXGlobal = false;
int gameDepthGlobal;
string name = "Castle vania";
const char* gameNameGlobal = name.c_str();
//wstring q = UTF8toWide(gameNameGlobal);
int frameRateGlobal = 60;
int colorModeGlobal;
bool isFullScreenGlobal = false;
D3DFORMAT backBufferFormatGlobal;
bool isBackgroundSoundGlobal = true;
bool isEffectSoundGlobal = true;
int mapWidthGlobal;
int mapHeightGlobal;
int maxSizeGlobal;
int minSizeGlobal;
RECT Window_Size;
int screenWidthGlobal = 800;
int screenHeightGlobal = 600;

HINSTANCE hInstanceGlobal;
HWND hWndGlobal;
LPDIRECT3D9 directGlobal;
LPDIRECT3DDEVICE9 deviceGlobal;
LPDIRECT3DSURFACE9 backBufferGlobal;
LPDIRECTINPUT8 directInputGlobal;
LPDIRECTINPUTDEVICE8 keyboardGlobal;
LPD3DXSPRITE spriteHandlerGlobal;

void GlobalTrace(char* format, ...) {
	string name = "C:\\Temp\\Sample_TH_game.log";
	const char* _traceFile = name.c_str();
	int _traEnumManager = 1;
	if (!_traEnumManager) return;
	FILE *f = stderr;
	if (_traceFile != NULL) {
		if (fopen_s(&f, _traceFile, "a") != 0) {
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
			return;
		}
	}
	va_list ap;
	va_start(ap, format);
	fprintf(f, format, ap);
	va_end(ap);
	fprintf(f, "\n");
	if (_traceFile != NULL) fclose(f);
}

void GlobalMessage(char* text) {
	MessageBox(hWndGlobal, text, "Sample TH", MB_OK);
}

void GlobalTitle(char* text) {
	SetWindowText(hWndGlobal, text);
}



