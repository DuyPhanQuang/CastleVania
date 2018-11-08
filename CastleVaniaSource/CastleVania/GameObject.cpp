#include "GameObject.h"

int GameObject::GetTag() {
	return tag;
}

//SweptAABBCollider* GameObject::GetCollider() { return sweptAABBCollider; };
Collider* GameObject::GetCollider()
{
	return collider;
}

void GameObject::SetBox(float x, float y, float w, float h, float vx, float vy) {
	//box collider cho game objec
	Box boxCollider;
	boxCollider.top = y;
	boxCollider.bottom = y - h;
	boxCollider.left = x;
	boxCollider.right = x + w;
	boxCollider.vx = vx;
	boxCollider.vy = vy;

	//sweptAABBCollider->SetBox(boxCollider); //build box collider
	collider->SetBox(boxCollider);

}

D3DXVECTOR3 GameObject::GetVelocity() {
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


GameObject::GameObject() {
	sprite = NULL;
}

GameObject::~GameObject() {
	if (sprite) {
		delete(sprite);
	}
	/*if (sweptAABBCollider)
		delete(sweptAABBCollider);*/
	if (collider)
		delete(collider);
}

bool GameObject::Initialize(LPDIRECT3DDEVICE9 _gDevice, const char* _file, float _x, float _y, int tag) {
	id = 0;
	isEnable = true;
	isDropItem = false;
	isMoveable = false;
	trigger = false;
	isAdded = false;

	if (!sprite) {
		sprite = new Sprite(_x, _y);
		if (!sprite->Initialize(_gDevice, _file))
			return false;
	}

	/*sweptAABBCollider = new SweptAABBCollider();*/
	collider = new Collider();

	//GAN TAG CHO OBJECT
	/*sweptAABBCollider->SetTag(tag);*/
	collider->SetTag(tag);
	this->tag = tag;

	SetSize(sprite->GetWidth(), sprite->GetHeight());
	SetPosition(sprite->GetPosition());

	colliderEffect = new ColliderEffect();
	colliderEffect->Initialize(_gDevice, COLLIDER_EFFECT_SPRITE, _x, _y - 20);

	return true;
}

bool GameObject::InitSprite(LPDIRECT3DDEVICE9 gDevice, const char * file, float x, float y) {
	if (!sprite) {
		sprite = new Sprite(x, y);
		if (!sprite->Initialize(gDevice, file))
			return false;
	}

	return true;
}

void GameObject::SetSize(float width, float height) {
	this->width = width;
	this->height = height;
}

void GameObject::Render(ViewPort *viewPort) {
	if (isEnable)
		sprite->Render(viewPort);
}

void GameObject::SetPosition(D3DXVECTOR3 position) {
	this->position = position;
}

void GameObject::SetPosition(float x, float y) {
	sprite->SetPosition(x, y);
}

void GameObject::SetEnable(bool _isEnable) {
	if (_isEnable)
	this->isEnable = _isEnable;
}

void GameObject::Reload() {
	isEnable = false;
	isInCamera = false;
	trigger = false;
}

void GameObject::Update(float gameTime) {}