#pragma once
#include "GameObject.h"
#include "Animated.h"

#define E_INVINCIBLE_TIME 0.4

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(int hp, int dame, int point);
	~Enemy();

	bool e_isInvincible;
	static float stopTime;

	virtual bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	virtual void Render(ViewPort *viewPort);
	virtual void Update(float gameTime);
	virtual void SetBox(float offsetX, float offsetY, float width, float height);
	virtual void CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject);
	virtual bool IsColliderWith(float gameTime, GameObject *object);

	virtual int GetHP() { return this->hp; };
	virtual void SetHP(int hp) { this->hp = hp; };
	int GetPoint() { return point; };
	void Reload();
	void Respawn(); //cai tu hoan sinh
	float respawnTime;
	float respawnTimeNeo;
	bool isIn;

	void GravityHandle(float gameTime);

private:

protected:
	Animated *anim;
	D3DXVECTOR3 velocity;
	float acceleration; //tang toc.lam cho quai di chuyen that hon
	int action;
	bool isLeft;

	int hp;
	int e_preHP;
	float e_invincibleTime;
	int hpC;
	int dame;
	int point;
	bool isGravity;
	bool isGrounded;

};

//Enemy::Enemy()
//{
//}
//
//Enemy::~Enemy()
//{
//}