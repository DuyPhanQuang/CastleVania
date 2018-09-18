#include <d3dx9.h>
#include "Utils.h"

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);

<<<<<<< HEAD:CastleVaniaSource/CastleVaniaSource/Utils.cpp
	if (result != D3D_OK)
=======
	if(result != D3D_OK)
>>>>>>> HANDLE_UTILS:CastleVaniaSource/CastleVania/CastleVania/Utils.cpp
	{
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		NULL);

<<<<<<< HEAD:CastleVaniaSource/CastleVaniaSource/Utils.cpp
	if (result != D3D_OK)
=======
	if(result != D3D_OK)
>>>>>>> HANDLE_UTILS:CastleVaniaSource/CastleVania/CastleVania/Utils.cpp
	{
		return NULL;
	}

	return surface;
}
