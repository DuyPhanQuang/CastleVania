
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//global

//view mode(used in contructor of game class)
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12
//
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024

extern struct Box
{
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy) {
		x = _x; //toa do 
		y = _y; //toa do
		w = _w; //chieu dai
		h = _h; //chieu rong
		vx = _vx; //van toc
		vy = _vy;
	}
	float x, y, w, h, vx, vy;
};

//cac bien duoc tham chieu duoc khai bao o  cap cao nhat (global). la tham chieu cua cac bien da duoc dinh nghia o ben global.cpp 

extern bool isInitedDXGlobal; //kiem tra neu dx da duoc khoi tao
extern int gameDepthGlobal; //chieu sau game
extern char* gameNameGlobal;	 //ten game
extern int frameRateGlobal; // (60)
extern int colorModeGlobal;
extern bool isFullScreenGlobal; //kiem tra che do cua so hay full
extern D3DFORMAT backBufferFormatGlobal;
extern int mapWidthGlobal; //dem cac o trong chieu dai map
extern int mapHeightGlobal; //dem cac o trong chieu rong map
extern int screenWidthGlobal;
extern int screenHeightGlobal;
extern bool isBackgroundSoundGlobal; //kiem tra nhac nen cua map co dang phat
extern bool isEffectSoundGlobal; //kiem tra nhac cua effect co dang phat
extern int maxSizeGlobal;
extern int minSizeGlobal;
extern RECT Window_Size;

extern HINSTANCE hInstanceGlobal;
extern HWND hWndGlobal;
extern LPDIRECT3D9 directXGlobal;
extern LPDIRECT3DDEVICE9 deviceGlobal;
extern LPDIRECT3DSURFACE9 backBufferGlobal;
extern LPDIRECTINPUT8 directInputGlobal;
extern LPDIRECTINPUTDEVICE8 keyboardGlobal;
extern LPD3DXSPRITE spriteHandlerGlobal; //ve ket cau

extern int currentFormGlobal;
extern int nextFormGlobal;

//viet chuoi vao tep truy tim
void GlobalTrace(char* format, ...);

void GlobalMessage(char* text);

void GlobalTitle(char* text);

#endif // 


