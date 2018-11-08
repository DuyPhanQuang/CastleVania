#include "BatAnim.h"

BatAnim::BatAnim() {}

BatAnim::~BatAnim() {}

bool BatAnim::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y) {
	if (!sprite) {
		sprite = new Sprite(x, y);
		if (!sprite->Initialize(gDevice, file))
			return false;
	}

	anim = new Animated();
	anim->Initialize(sprite, 16, 16, 0.15f);

	std::vector<D3DXVECTOR2> batAnim;
	batAnim.push_back(D3DXVECTOR2(0, 0));
	batAnim.push_back(D3DXVECTOR2(1, 0));

	anim->AddAnimated(0, batAnim);
	return true;
}

void BatAnim::Render(ViewPort *viewPort) {
	anim->Render(sprite, true, viewPort);
}

void BatAnim::Update(float gameTime, float vx, float vy) {
	sprite->SetPosition(sprite->GetPosition().x + vx * gameTime, sprite->GetPosition().y + vy * gameTime);
	anim->Update(gameTime);
}

void BatAnim::SetPosition(float x, float y) {
	sprite->SetPosition(D3DXVECTOR3(x, y, 0));
}