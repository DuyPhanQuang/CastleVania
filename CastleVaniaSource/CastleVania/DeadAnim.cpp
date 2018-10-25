#include "DeadAnim.h"

DeadAnim::DeadAnim() {};
DeadAnim::~DeadAnim() {};

bool DeadAnim::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y) {
	if (!sprite) {
		sprite = new Sprite(x, y);
		if (!sprite->Initialize(gDevice, file))
			return false;
	}

	anim = new Animated();
	anim->Initialize(sprite, 42.6f, 44.0f, 0.15f); //f_W , f_H, f_T
	std::vector<D3DXVECTOR2> deadAnim;
	deadAnim.push_back(D3DXVECTOR2(0,0));
	deadAnim.push_back(D3DXVECTOR2(1,0));
	deadAnim.push_back(D3DXVECTOR2(2,0));

	anim->AddAnimated(0, deadAnim);
	return true;
}

void DeadAnim::Render(ViewPort *viewPort) {
	anim->Render(sprite, true, viewPort);
}

void DeadAnim::Update(float gameTime) {
	anim->Update(gameTime);
}

void DeadAnim::SetPosition(float x, float y) {
	sprite->SetPosition(D3DXVECTOR3(x, y, 0));
}

bool DeadAnim::CheckDoAllFrame() { return anim->CheckDoAllFrame(); }