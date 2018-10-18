#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground(int width, int height);
	~Ground();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	void Render(ViewPort *viewPort);

protected:
	int width;
	int height;
};

//Ground::Ground()
//{
//}
//
//Ground::~Ground()
//{
//}
