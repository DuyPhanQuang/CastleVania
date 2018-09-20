#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"

class Graphics
{
private: 
	LPDIRECT3DDEVICE9 pDevice3d;
	LPDIRECT3D9 pDirect3d;
	D3DPRESENT_PARAMETERS d3dpp;

	HRESULT result;
	HWND hWnd;
	bool fullscreen;
	int width;
	int height;

	D3DCOLOR color;
	//khoi tao D3D presentation parameters
	void InitD3Dpp();

	//Short hand for IDirect3DDevice9 *device
public:
	Graphics();
	~Graphics();
	//khoi tao doi tuong directx graphics

	bool Initialize(HWND hw);
	//cac method ve len device

	void Clear();
	void Begin();
	void End();
	void Present();

	//tra ve device3D

	LPDIRECT3DDEVICE9 GetDevice() {
		return pDevice3d;
	}
	// Shorthand for IDirect3DDevice9 *device
	void SetColor(D3DCOLOR color) {
		this->color = color;
	}
};
#endif // !_GRAPHICS_H_

