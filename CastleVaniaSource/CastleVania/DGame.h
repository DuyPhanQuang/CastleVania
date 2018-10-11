#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

#ifndef DGAME_H

class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 
	LPKEYEVENTHANDLER keyHandler;
	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

public:
	void Init(HWND hWnd);
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame * GetInstance();

	~CGame();
};

#endif // !DGAME_H
