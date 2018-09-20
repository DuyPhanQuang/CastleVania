#pragma once
#include <d3dx9.h>
#include "define.h"

class ViewPort
{
public:
	ViewPort(float x, float y);
	~ViewPort();

	//chuyen tu toa do the gioi thuc sang toa do viewport
	D3DXVECTOR3 SetPositionInViewPort(D3DXVECTOR3 position);

	//set toa do cua camera trong the gioi thuc world(di chuyen camera)
	void SetCameraPosition(float x, float y);

	//lay toa do cua camera trong the gioi thuc
	D3DXVECTOR3 GetCameraPosition();

private:
	D3DXVECTOR3 cameraPosition; //toa do cua camera trong world
	RECT *region;
};

//ViewPort::ViewPort()
//{
//}
//
//ViewPort::~ViewPort()
//{
//}