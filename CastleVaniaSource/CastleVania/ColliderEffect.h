#pragma once
#include "GSprite.h"

class ColliderEffect
{
public:
	ColliderEffect();
	~ColliderEffect();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	void Render(ViewPort *viewPort);
	void Update(float _gameTime);
	void SetPosition(float x, float y);
	void SetVisible(bool _isVisible) { isVisible = _isVisible; };

private:
	Sprite *sprite;
	bool isVisible;
	float timeDelay;
};

//ColliderEffect::ColliderEffect()
//{
//}
//
//ColliderEffect::~ColliderEffect()
//{
//}
