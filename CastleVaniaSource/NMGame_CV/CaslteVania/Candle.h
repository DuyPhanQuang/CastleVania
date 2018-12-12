#pragma once
#include "Enemy.h"
class Candle :	public Enemy
{
private:
	void InitAnim();
public:
	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	void Render(ViewPort *viewPort);
	void Update(float gameTime);
	Candle();
	~Candle();
};

