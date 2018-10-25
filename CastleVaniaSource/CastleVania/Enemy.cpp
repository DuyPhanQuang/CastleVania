#include "Enemy.h"

Enemy::Enemy(int _hp, int _dame, int _point) {
	isGravity = true;
	isGrounded = false;
	this->isLeft = false;
	this->hp = _hp;
	this->dame = _dame;
	this->point = _point;
	this->respawnTime = 1;
	hpC = hp;
}

Enemy::~Enemy() {
	if (anim) {
		delete(anim);
		anim = NULL;
	}
}

float Enemy::stopTime = 0;

bool Enemy::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag) {
	isMoveable = true;
	isIn = false;

	e_invincibleTime = E_INVINCIBLE_TIME;
	e_preHP = hp;
	e_isInvincible = false;

	return GameObject::Initialize(gDevice, file, x, y, tag);
}

void Enemy::Reload() {
	isEnable = false;
	isDead = true;
	isInCamera = false;
	trigger = false;

	hp = hpC;
	e_invincibleTime = E_INVINCIBLE_TIME;
	e_preHP = hp;
	e_isInvincible = false;

	sprite->SetPosition(positionC);
	Enemy::SetBox(0, 0, 0, 0);
	//*region = *regionC
}

void Enemy::Respawn() {
	isEnable = true;
	isDead = false;
	hp = hpC;
	e_invincibleTime = E_INVINCIBLE_TIME;
	e_preHP = hp;
	e_isInvincible = false;
}

void Enemy::Render(ViewPort *viewPort) {
	if (!isDead && isEnable)
		anim->Render(sprite, isLeft, viewPort);
	/*else if (isDead)
		deadEffect->Render(viewPort);*/
	if (isEnable)
		colliderEffect->Render(viewPort);
}

void Enemy::Update(float gameTime) {
	if (!isDead) {
		if (isEnable == true) {
			respawnTime = 0;
			if (hp < e_preHP) {
				e_isInvincible = true;
				e_preHP = hp;
			}
			if (hp <= 0) {
				isDead = true;
				return;
			}

			//trong luc faded
			if (e_isInvincible == true) {
				e_invincibleTime -= gameTime;
				if (e_invincibleTime <= 0) {
					e_invincibleTime = E_INVINCIBLE_TIME;
					e_isInvincible = false;
				}
			}
			else {
				if (stopTime <= 0 || GetTag() == TAG_SIMON) {
					sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime,
						sprite->GetPosition().y + velocity.y  * gameTime);
					anim->DoAnimated(action);
					anim->Update(gameTime);
				}
				else {
					stopTime -= gameTime;
				}
				SetPosition(sprite->GetPosition());
			}

			deadEffect->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y);
		}
		else
			respawnTime += gameTime;
	}
	else
		UpdateEffect(gameTime);
	colliderEffect->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y - 20);
	colliderEffect->Update(gameTime);
}