#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GSprite.h"

class GCamera
{
public:
	D3DXVECTOR2 viewport;		//thiet lap toa do cua camera
	int right, left;

	GCamera();
	void UpdateCamera(int x);
	void SetSizeMap(int _max, int _min);
	D3DXVECTOR2 Transform(int x, int y);		//ham transform, chuyen toa do viewport ve toa do world
};

#endif