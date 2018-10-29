#include "Door.h"

Door::Door() {}
Door::~Door() {}

void Door::InitAnim() {
	anim = new Animated();
	anim->Initialize(spriteDoorAnim, 50, 96, 0.2);

	std::vector<D3DXVECTOR2> openingDoor;
	openingDoor.push_back(D3DXVECTOR2(0, 0));
	openingDoor.push_back(D3DXVECTOR2(1, 0));

	std::vector<D3DXVECTOR2> closingDoor;
	closingDoor.push_back(D3DXVECTOR2(1, 0));
	closingDoor.push_back(D3DXVECTOR2(1, 0));
	closingDoor.push_back(D3DXVECTOR2(0, 0));

	anim->AddAnimated(OPENING_DOOR, openingDoor); //0
	anim->AddAnimated(CLOSING_DOOR, closingDoor); //1

	doorAction = OPENING_DOOR;
}

bool Door::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag) {
	if (!GameObject::Initialize(gDevice, file, x, y, tag))
		return false;
	isOccurred = false;
	isDrawable = false;
	setedDoAllFrame = false;
	isSetPositionAnim = false;
	spriteDoorAnim = new Sprite(x - 16, y);
	if (!spriteDoorAnim->Initialize(gDevice, DOOR_SPRITE))
		return false;
	
	InitAnim();

	return true;
}

void Door::Render(ViewPort *viewPort) {
	if (isDrawable) {
		anim->DoAnimated(doorAction);
		anim->Render(spriteDoorAnim, isLeft, viewPort);
	}
	else
		sprite->Render(viewPort);
}

void Door::Update(float gameTime) {
	SetBox(sprite->GetPosition().x - 15, sprite->GetPosition().y, 16 + 30, 96, 0, 0);
	if (isOccurred)
		collider->SetTag(TAG_GROUND);
}

void Door::UpdateAnim(float gameTime) {
	anim->Update(gameTime);
}

void Door::DoAnim() {
	anim->SetDoAllFrame(false);
	anim->DoAnimated(doorAction);
}

void Door::SetSpriteXPosition(int _x) {
	if (!isSetPositionAnim)
		spriteDoorAnim->SetPosition(D3DXVECTOR3(spriteDoorAnim->GetPosition().x + _x, spriteDoorAnim->GetPosition().y, 0));
	isSetPositionAnim = true;
}