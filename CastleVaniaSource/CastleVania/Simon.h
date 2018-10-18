#pragma once
#include "Input.h"
#include "GameObject.h"

#define INVINCIBLE_TIME 2

class Simon : public GameObject
{
public:
	Simon(int hp, int damage, int point);
	~Simon();
	bool Initialize(LPDIRECT3DDEVICE9 _gDevice, const char * _file, float _x, float _y, int tag);
	void Reload();
	void Render(ViewPort *viewPort);

	void CreateAnimation();
	void Update(float gameTime);
	void UpdateKeyboard(float gameTime);
	void KeyBoardHandle(float gameTime);

	bool GetIsLeft() { return isLeft; };
	void SetIsLeft(bool status) { isLeft = status; };

	void Move();
	void Jump();
	void Sit();
	void Stand();
	void Hurted();

	bool nextStage;

	bool CanControllKeyboard() { return canControlKeyboard; }
protected:
	bool isLeft;
private:
	int currentAnimID;
	float simonSpeed;
	bool isInvincible;
	float invincibleTime;

	bool canControlKeyboard;
};
