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

void Enemy::SetBox(float offsetWidth, float offsetHeight, float offsetX, float offsetY) {
	GameObject::SetBox(sprite->GetPosition().x - offsetX, sprite->GetPosition().y - offsetY, anim->frameWidth - offsetWidth, anim->frameHeight - offsetHeight, velocity.x, velocity.y);
}

void Enemy::CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++) {
		if ((*i)->GetCollider()->GetTag() == TAG_GROUND) {
			Box tempBox = (*i)->GetCollider()->GetBox();
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox())) {
				isGrounded = false;
			}
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox())) {
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollide >= 0.0f && timeCollide < 1.0f)) {
					if (normalY == 1) {
						sprite->SetPosition(sprite->GetPosition().x, collider->GetBox().top + gameTime * timeCollide * velocity.y + 0.1);
						velocity.y = 0;
						isGrounded = true;
						return;
					}
				}
			}
			else
				isGrounded = false;
		}
	}
}

void Enemy::GravityHandle(float gameTime) {
	velocity.y += EARTH_ACCELERATION * gameTime;
}

bool Enemy::IsColliderWith(float gameTime, GameObject * object) {
	float normalX = 0; 
	float normalY = 0;
	float timeCollide;
	Box tempBox = object->GetCollider()->GetBox();
	if (collider->AABBCheck(collider->GetBox(), object->GetCollider()->GetBox())) {
		return true;
	}
	Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
	if (collider->AABBCheck(broadphaseBox, object->GetCollider()->GetBox())) {
		Box tempBox = object->GetCollider()->GetBox();
		timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), object->GetCollider()->GetBox(), normalX, normalY);
		if ((timeCollide >= 0.0f && timeCollide < 1.0f)) {
			return true;
		}
		else return false;


		return false;
	}
}