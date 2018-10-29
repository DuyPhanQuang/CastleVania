#include "Simon.h"


Simon::Simon(int hp, int damage, int point) : Enemy(hp, damage, point) {
	respawnTime = 0;
	respawnTimeNeo = 0;
}

Simon::~Simon() {
	SAFE_DELETE(anim);
}

bool Simon::Initialize(LPDIRECT3DDEVICE9 _gDevice, const char* _file, float _x, float _y, int tag)
{
	if (!GameObject::Initialize(_gDevice, _file, _x, _y, tag))
		return false;
	isLeft = false;

	isCollideLeftWall = false;
	isCollideRightWall = false;

	simonSpeed = SPEED; //150
	canControlKeyboard = true;
	doorCollideDirection = 0;
	isGoingThrowDoor = false;

	deadTime = 0;
	this->CreateAnimation();

	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;
	nextStage = false;

	prevHP = hp;
	life = 3;

	energy = 0;

	return true;
}

void Simon::Reload() {

	prevHP = hp;
	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;
	nextStage = false;
	isGravity = false;
	isGrounded = false;
	this->isLeft = false;
	isCollideLeftWall = false;
	isCollideRightWall = false;

	SetSize(sprite->GetWidth(), sprite->GetHeight());
	SetPosition(sprite->GetPosition());
	canControlKeyboard = true;
}

void Simon::Reset(D3DXVECTOR3 pos) {
	isLeft = false;
	isGrounded = false;
	velocity.x = 0;
	action = STAND;
	isDead = false;
	SetPosition(pos.x, pos.y + 100);
	SetEnable(true);
	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;
	SetHP(16);
	prevHP = hp;
	canControlKeyboard = true;
}

void Simon::SetInvincible(int time) {
	invincibleTime = time;
	isInvincible = true;
}

void Simon::CreateAnimation() {
	anim = new Animated();
	anim->Initialize(sprite, 60.0f, 66.0f, 0.15f);

	//khoi tao anim dung yen
	std::vector<D3DXVECTOR2> standAnimation;
	standAnimation.push_back(D3DXVECTOR2(0, 0));
}

void Simon::Update(float gameTime) {
	/*if (velocity.y > 0)
		currentDirection = 1;
	else if (velocity < 0)
		currentDirection = -1;
*/
	if (action != SIT && action != HIT_SIT && action != JUMP)
		Enemy::SetBox(30, 0, -15, 0);
	else
		Enemy::SetBox(30, 16, -15, 16);

	if (!isDead) {
		if (isEnable == true) {
			if (hp < prevHP) {
				prevHP = hp;
				isInvincible = true;
			}

			if (hp <= 0) {
				isDead = true;
				respawnTime = 0.0f;
			}

			sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime, sprite->GetPosition().y + velocity.y * gameTime);
			anim->DoAnimated(action);
			anim->Update(gameTime);
			SetPosition(sprite->GetPosition());

		}
	}
	else {
		if (isGrounded) {
			isInvincible = false;
			canControlKeyboard = false;
			action = DEAD;
			respawnTime += gameTime;
			if (respawnTime > 2) {
				respawnTime = 0.0f;
				isDead = false;
				isEnable = false;
			}
		}
		else {
			sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime, sprite->GetPosition().y + velocity.y * gameTime);
		}
		anim->DoAnimated(action);
		anim->Update(gameTime);
	}

	//
	if (action == HIT_SIT || action == HIT_STAND || action == HIT_UP_STAIR)
		isFighting = !anim->CheckDoAllFrame();

	//
	if (isInvincible)
		isSplashing = isSplashing ? false : true;
	else
		isSplashing = false;
}

void Simon::Render(ViewPort *viewPort) {
	if (!isSplashing) {
		if (isFighting && (action == HIT_SIT || action == HIT_STAND || action == HIT_UP_STAIR || action == HIT_DOWN_STAIR)) {
			//
		}
		anim->Render(sprite, isLeft, viewPort);
		//
	}
}

D3DXVECTOR3 Simon::GetVelocity() {
	return velocity;
}

void Simon::UpdateKeyboard(float gameTime) {
	if (canControlKeyboard) {
		if ((action != HURTED || isGrounded == true) && !(action == HIT_STAND && isGrounded == false)) {
			if (IsKeyPress(DIK_SPACE) && isGrounded) {
				if (action == SIT || action == JUMP)
					return;
				action = JUMP;
				Jump();
				isGrounded = false;
			}
			//
			if (isGrounded && velocity.y > 0 && action != JUMP && action != HURTED) {
				//
				Stand();
			}
			else if (isGrounded && velocity.y == 0) {
				//
				Stand();
			}
			if (IsKeyDown(DIK_DOWN)) {
				//
				if (action == JUMP || action == HURTED)
					return;
				action = SIT;
				Sit();
			}

			if (IsKeyDown(DIK_LCONTROL)) {
				if (action == SIT)
					action = HIT_SIT;
				else
					action = HIT_STAND;
				Fight();
				return;
			}

			if (IsKeyPress(DIK_RCONTROL) || IsKeyPress(DIK_0)) {
				//
			}

			if (isGrounded == true) {
				velocity.x = 0;
			}

			if (IsKeyDown(DIK_LEFT) && !isOnStair) {
				if (action == JUMP && isGrounded == false)
					return;
				isLeft = true;
				if (action != SIT) {
					action = MOVE;
					Move();
				}
			}

			if (IsKeyDown(DIK_RIGHT && !isOnStair)) {
				if (action == JUMP && isGrounded == false)
					return;
				isLeft = false;
				if (action != SIT) {
					action = MOVE;
					Move();
				}
			}
		}
	}
}

//move
void Simon::Move() {
	action = MOVE;
	velocity.x = ((isLeft) ? -1 : 1) * simonSpeed;
}

//jump
void Simon::Jump() {
	velocity.y = JUMP_FORCE;
}

//sit
void Simon::Sit() {
	velocity.x = 0;
	velocity.y = 0;
}

//stand
void Simon::Stand() {
	if (action != STAND)
		velocity.x = 0;
	action = STAND;
	velocity.y = 0;
	//
}

//fight
void Simon::Fight() {
	isFighting = true;
	//
	Fighting();
}

//fighting
void Simon::Fighting() {
	if (!isFighting) {
		if (action == HIT_SIT) {
			action = SIT;
			Sit();
		}
		else {
			if (!isOnStair) {
				action = STAND;
				Stand();
			}
			else {
				if (currentDirection > 0)
					action = STANDING_UP;
				else action = STANDING_DOWN;
			}
		}
		//
	}
	else {
		//
		if (isGrounded)
			velocity.x = 0;
	}
}

void Simon::StandOnStair() {
	velocity.x = 0;
	velocity.y = 0;
}

void Simon::KeyBoardHandle(float gameTime) {
	if (action == HIT_SIT || action == HIT_STAND || action == HIT_UP_STAIR || action == HIT_DOWN_STAIR) {
		Fighting();
	}
	//
	else UpdateKeyboard(gameTime);
}

void Simon::Hurted() {
	velocity.x = velocity.x = ((isLeft) ? 1 : -1) * simonSpeed;
	velocity.y = JUMP_FORCE - 100;
	sprite->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y + 1);
}


//
void Simon::CheckCollider(float gameTime, std::vector<GameObject*>* listGameObject) {
	//
	this->CheckColliderWithGround(gameTime, listGameObject);
	/*this->CheckColliderWithMovableGround(gameTime, listGameObject);*/

	if (isInvincible == false && !isDead) {
		/*this->CheckColliderWithEnemy(gameTime, listGameObject);*/
	}
	else {
		invincibleTime -= gameTime;
		if (invincibleTime < 0) {
			isInvincible = false;
			invincibleTime = INVINCIBLE_TIME;
		}
	}
}

void Simon::CheckColliderWithGround(float gameTime, std::vector<GameObject*>* listGameObject) {
	float normalX = 0;
	float normalY = 0;
	//
}

void Simon::CheckColliderWithGround(float gameTime, GameObject *gameObject) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;
	Box tempBox = gameObject->GetCollider()->GetBox();
	if (collider->AABBCheck(collider->GetBox(), gameObject->GetCollider()->GetBox())) {
		isGrounded = false;
	}
	Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
	if (collider->AABBCheck(broadphaseBox, gameObject->GetCollider()->GetBox())) {
		Box tempBox = gameObject->GetCollider()->GetBox();
		timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), gameObject->GetCollider()->GetBox(), normalX, normalY);
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

void Simon::CheckColliderWith(float gameTime, GameObject *object) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	if (object->GetTag() == TAG_GROUND) {
		Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
		if (collider->AABBCheck(broadphaseBox, object->GetCollider()->GetBox())) {
			Box tempBox = object->GetCollider()->GetBox();
			timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), object->GetCollider()->GetBox(), normalX, normalY);
			if ((timeCollide >= 0.0f && timeCollide < 1.0f)) {
				if (normalX == 1 && !isOnStair) {
					sprite->SetPosition(collider->GetBox().left + gameTime * timeCollide * velocity.x - 15, sprite->GetPosition().y);
				}
				if (normalX == -1 && !isOnStair) {
					sprite->SetPosition(collider->GetBox().left + gameTime * timeCollide * velocity.x - 15, sprite->GetPosition().y);
				}
			}
		}
	}

	if (object->GetTag() == TAG_GROUND) {
		Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
		if (collider->AABBCheck(collider->GetBox(), object->GetCollider()->GetBox())) {
			SetHP(GetHP() - 2);
			isGrounded = false;
			action = HURTED;
			Hurted();
			//
		}
		else if (collider->AABBCheck(broadphaseBox, object->GetCollider()->GetBox())) {
			Box tempBox = object->GetCollider()->GetBox();
			timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), object->GetCollider()->GetBox(), normalX, normalY);
			if ((timeCollide > 0.0f && timeCollide < 1.0f)) {
				SetHP(GetHP() - 2);
				isGrounded = false;
				action = HURTED;
				Hurted();
				//
			}
		}
	}
}

void Simon::CheckColliderWithDoor(float gameTime, std::vector<GameObject*>* listGameObject) {
	float normalX = 0; 
	float normalY = 0;
	float timeCollide;

	//lap de check simon co va cham voi door ko
	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++) {
		if ((*i)->GetCollider()->GetTag() == TAG_DOOR) {
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox())) {
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollide >= 0.0f && timeCollide < 1.0f)) {
					collideDoor = (*i)->GetPosition();
					doorCollideDirection = normalX;
					door = (Door*)(*i);
				}
			}
		}
	}
}

bool Simon::IsColliderWith(float gameTime, GameObject * object) {
	return Enemy::IsColliderWith(gameTime, object);
}