#pragma once

#include "Animated.h"

class BatAnim {
private:
	Sprite* sprite;
	Animated *anim;
public:
	BatAnim();
	~BatAnim();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	void Render(ViewPort *viewPort);
	void Update(float gameTime, float vx, float vy);
	void SetPosition(float x, float y);
};
