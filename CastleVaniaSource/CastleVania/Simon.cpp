#include "Simon.h"

Simon::Simon(int hp, int damage, int point) {
	
}

Simon::~Simon() {
}

bool Simon::Initialize(LPDIRECT3DDEVICE9 _gDevice, const char* _file, float _x, float _y, int tag)
{
	if (!GameObject::Initialize(_gDevice, _file, _x, _y, tag))
		return false;
	canControlKeyboard = true;
	/*this->CreateAnimation();*/
	nextStage = false;
	return true;
}

void Simon::Reload() {
	nextStage = false;
	this->isLeft = false;

	SetSize(sprite->GetWidth(), sprite->GetHeight());
	SetPosition(sprite->GetPosition());
	canControlKeyboard = true;
}