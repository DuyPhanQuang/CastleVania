#pragma once
#include "GSprite.h"
#include "Graphics.h"

class GameObject
{
public:
	bool isInCamera;
	bool trigger;
	RECT *regionC;
	D3DXVECTOR3 positionC;
	bool isAdded;
	bool isDropItem;

	 bool Initialize(LPDIRECT3DDEVICE9 gDevie, const char* file, float x, float y, int tag);
	virtual bool InitSprite(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	virtual void Render(ViewPort *viewPort);
	virtual void Update(float gameTime);
	virtual void Reload();

	float GetWidth() { return width; }
	float GetHeight() { return height; }
	D3DXVECTOR3 GetPosition() { return sprite->GetPosition(); }
	void SetSize(float width, float height);
	void SetPosition(D3DXVECTOR3 position);
	void SetPosition(float x, float y);
	void SetEnable(bool enable);
	bool IsEnable() { return isEnable; }


	int GetTag();
	GameObject();
	~GameObject();

	void SetColor(D3DCOLOR color) { sprite->SetColor(color); }
	void SetPosition(D3DXVECTOR3 position);

private:
	int tag;
	int id;

protected:
	Sprite* sprite;
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