#include "GameObject.h"

int GameObject::GetTag() {
	return tag;
}

GameObject::GameObject() {
	sprite = NULL;
	region = NULL;
	if (!region) 
		region = new RECT();

}

GameObject::~GameObject() {
	if (sprite) {
		delete(sprite);
	}
	if (region) {
		delete(region);
	}
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

	SetSize(sprite->GetWidth(), sprite->GetHeight());
	SetPosition(sprite->GetPosition());

	return true;
}

bool GameObject::InitSprite(LPDIRECT3DDEVICE9 gDevice, const char *file, float x, float y) {
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
		isDead = false;
	this->isEnable = _isEnable;
}

void GameObject::Reload() {
	isEnable = false;
	isInCamera = false;
	trigger = false;
	sprite->SetPosition(positionC);
	*region = *regionC;
}

void GameObject::Update(float gameTime) {}