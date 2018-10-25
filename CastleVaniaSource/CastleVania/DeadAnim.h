#pragma once
#include "GSprite.h"
#include "Animated.h"

class DeadAnim
{
public:
	DeadAnim();
	~DeadAnim();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	void Render(ViewPort *viewPort);
	void Update(float gameTime);
	void SetPosition(float x, float y);
	bool CheckDoAllFrame();
private:
	Sprite *sprite;
	Animated *anim;
};

//DeadAnim::DeadAnim()
//{
//}
//
//DeadAnim::~DeadAnim()
//{
//}
