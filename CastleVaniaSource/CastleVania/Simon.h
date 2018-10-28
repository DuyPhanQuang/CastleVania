#pragma once
#include "Input.h"
#include "GameObject.h"
//#include "SweptAABBCollider.h"
#include "Animated.h"
#include "Enemy.h"


#define INVINCIBLE_TIME 2

class Simon : public Enemy
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
	void CheckColliderWith(float gameTime, GameObject *object);
	/*bool IsColliderWith(float gameTime, GameObject *object);*/

	bool GetIsLeft() { return isLeft; };
	void SetIsLeft(bool status) { isLeft = status; };
	void SetAction(int action) { this->action = action; }

	void Move();
	void Jump();
	void Sit();
	void Stand();
	void Hurted();

	bool nextStage;

	int GetNoSubWeapon() { return noSubWeapon; };
	D3DXVECTOR3 GetVelocity();
	void SetVelocity(D3DXVECTOR3 _velocity) { velocity = _velocity; };
	D3DXVECTOR3 GetCollideDoor() { return collideDoor; };
	void SetCanControlKeyboard(bool status) { canControlKeyboard = status; };
	bool CanControllKeyboard() { return canControlKeyboard; }
protected:
	bool isLeft;
	int action;
private:
	int noSubWeapon;
	int currentAnimID;
	float simonSpeed;
	bool isInvincible;
	float invincibleTime;

	bool canControlKeyboard;
	bool isCollideLeftWall;
	bool isCollideRightWall;

	int directionX = 0, directionY = 0;

	D3DXVECTOR3 collideDoor;
	float timeCollideGround;
	float deadTime;
};
