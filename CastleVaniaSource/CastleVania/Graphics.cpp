#include "Graphics.h"

//constructor
Graphics::Graphics() {
	pDevice3d = NULL;
	pDirect3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
}

//destructor
Graphics::~Graphics() {
	if (pDevice3d != NULL)
		pDevice3d->Release();
	if (pDirect3d != NULL)
		pDirect3d->Release();
}

//khoi tao DirectX graphics
bool Graphics::Initialize(HWND hw) {
	color = D3DCOLOR_XRGB(0, 0, 0);
	hWnd = hw;
	fullscreen = FULLSCREEN;

	//khoi tao doi tuong directX 3D
	pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (pDirect3d == NULL)
		MessageBox(NULL, "Error initializing DirectX 3D", "Error", MB_OK);

	//khoi tao D3D presentation parameter
	InitD3Dpp();

	//Xac dinh card do hoa duoc ho tro
	D3DCAPS9 caps;
	DWORD behavior;
	result = pDirect3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1,1))
		// Use software-only processing
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		// Use hardware-only processing
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	//tao doi tuong DirectX Device
	result = pDirect3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		behavior,
		&d3dpp,
		&pDevice3d
	);
	if (FAILED(result)) {
		MessageBox(NULL, "Error creating DirectX 3D Device", "Error", MB_OK);
		return false;
	}
	return true;
}

//tao D3D doi so tham chieu (presentation parameter)
void Graphics::InitD3Dpp() {
	try {
		//gan tat ca cac gia tri ban dau la 0
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		//dien cac tham so can thiet
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; //day la 24bit color
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // su dung config cua desktop
			d3dpp.BackBufferCount = 1;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3dpp.hDeviceWindow = hWnd;
			d3dpp.Windowed = !(fullscreen);

	}
	catch (...) {
		MessageBox(NULL, "Error tao D3D doi so tham chieu", "Error", MB_OK);
	}
}

void Graphics::Clear() {
	// 2nd param is set to NULL so that it clears the entire back buffer
	pDevice3d->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Graphics::Begin() {
	pDevice3d->BeginScene();
}

void Graphics::End() {
	pDevice3d->EndScene();
}
void Graphics::Present() {
	// Present our scene to the window
	pDevice3d->Present(NULL, NULL, NULL, NULL);
}