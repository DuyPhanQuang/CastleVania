#pragma once
#include "GSprite.h"
#include "Graphics.h"
#include "ColliderEffect.h"
//#include "SweptAABBCollider.h"
#include "DeadAnim.h"
#include "Collider.h"

class GameObject
{
public:
	bool isInCamera;
	bool trigger;
	RECT *regionC;
	D3DXVECTOR3 positionC;
	bool isAdded;
	bool isDropItem;

	virtual bool Initialize(LPDIRECT3DDEVICE9 gDevie, const char* file, float x, float y, int tag);
	virtual bool InitSprite(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	virtual void Render(ViewPort *viewPort);
	virtual void Update(float gameTime);
	virtual void Reload();
	virtual void SetBox(float x, float y, float w, float h, float vx, float vy);
	virtual D3DXVECTOR3 GetVelocity();

	/*SweptAABBCollider* GetCollider();*/
	Collider* GetCollider();

	ColliderEffect* GetColliderEffect() { return colliderEffect; };
	virtual void CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject) {}

	float GetWidth() { return width; }
	float GetHeight() { return height; }
	D3DXVECTOR3 GetPosition() { return sprite->GetPosition(); }
	void SetSize(float width, float height);
	void SetPosition(D3DXVECTOR3 position);
	void SetPosition(float x, float y);
	void SetEnable(bool enable);
	bool IsEnable() { return isEnable; }
	void SetDead(bool _isDead) { isDead = _isDead; };
	bool IsDead() { return isDead; }
	void UpdateEffect(float gameTime);

	void SetID(int id) { this->id = id; };
	int GetID() { return id; };


	void SetMovable(bool isMoveable) { this->isMoveable = isMoveable; };
	bool IsMovable() { return this->isMoveable; }

	int GetTag();
	GameObject();
	~GameObject();

	void SetColor(D3DCOLOR color) { sprite->SetColor(color); }

private:
	int tag;
	int id;

protected:
	Sprite* sprite;
	/*SweptAABBCollider* sweptAABBCollider;*/
	Collider* collider;
	DeadAnim *deadEffect;
	ColliderEffect *colliderEffect;
	RECT *region;
	float width;
	float height;
	D3DXVECTOR3 position;
	bool isEnable;
	bool isDead;
	bool isMoveable;
};


//GameObject::GameObject()
//{
//}
//
//GameObject::~GameObject()
//{
//}