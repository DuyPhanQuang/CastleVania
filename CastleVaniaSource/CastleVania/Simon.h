#pragma once
#include "Input.h"
#include "GameObject.h"
//#include "SweptAABBCollider.h"
#include "Animated.h"
#include "Enemy.h"
#include "Door.h"
#include "Collider.h"


#define INVINCIBLE_TIME 2

class Simon : public Enemy
{
public:
	static int score;
	D3DXVECTOR3 simonCheckpoint;
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
	bool IsColliderWith(float gameTime, GameObject *object);

	bool GetIsLeft() { return isLeft; };
	void SetIsLeft(bool status) { isLeft = status; };

	void Move();
	void Jump();
	void Sit();
	void Stand();
	void Hurted();
	void Fight();

	bool nextStage;

	int GetNoSubWeapon() { return noSubWeapon; };
	D3DXVECTOR3 GetVelocity();
	void SetVelocity(D3DXVECTOR3 _velocity) { velocity = _velocity; };
	D3DXVECTOR3 GetCollideDoor() { return collideDoor; };
	void SetCanControlKeyboard(bool status) { canControlKeyboard = status; };
	bool CanControllKeyboard() { return canControlKeyboard; };
	bool IsGoingThrowDoor() { return isGoingThrowDoor; };
	void Reset(D3DXVECTOR3 pos);
	void SetInvincible(int time);

	void CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject);
	void CheckColliderWithGround(float gameTime, GameObject *gameObject);
	void CheckColliderWithGround(float gameTime, std::vector<GameObject*> * listGameObject);
	void CheckColliderWithWall(float gameTime, std::vector<GameObject*>* listGameObject);
	void CheckColliderWithEnemy(float gameTime, std::vector<GameObject*>* listGameObject);
	void CheckColliderWithDoor(float gameTime, std::vector<GameObject*>* listGameObject);

	void CollideWithDoorHandle(float gameTime, std::vector<GameObject*>* listGameObject, ViewPort* viewPort);

	bool IsInvincible() { return isInvincible; };
	bool IsColliderWithCheckPoint(float gameTime, std::vector<GameObject*>* listGameObject);
	int GetAction() { return action; };
	int GetEnergy() { return this->energy; };
	void SetEnergy(int energy) { this->energy = energy; };
	int GetLife() { return life; };
	void SetAction(int action) { this->action = action; }

protected:
	bool isLeft;
	int action;
private:

	/*bien nay dung de xac dinh vua roi simon di len hay xuong cau thang*/
	int currentDirection; // -1 0 1 , xuong - len

	int prevHP;
	int life;
	int energy;
	int doorCollideDirection;
	int noSubWeapon;
	int currentAnimID;
	float simonSpeed;
	float invincibleTime;

	bool isFighting;

	bool isInvincible;
	bool canControlKeyboard;
	bool isCollideLeftWall;
	bool isCollideRightWall;
	bool isGoingThrowDoor;

	int directionX = 0, directionY = 0;

	D3DXVECTOR3 collideDoor;
	Door *door;
	float timeCollideGround;
	float deadTime;
};
