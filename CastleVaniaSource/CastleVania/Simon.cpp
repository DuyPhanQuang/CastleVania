#include "Simon.h"

int Simon::score = 0;

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
	//isGoingThrowDoor = false;
	currentDirection = 0;
	deadTime = 0;
	this->CreateAnimation();

	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;
	nextStage = false;

	noSubWeapon = 1;
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

	//Khoi tao animation luc roi
	std::vector<D3DXVECTOR2> fallAnimation;
	fallAnimation.push_back(D3DXVECTOR2(0, 0));

	// Khoi tao animation luc di chuyen
	std::vector<D3DXVECTOR2> moveAnimation;
	moveAnimation.push_back(D3DXVECTOR2(0, 0));
	moveAnimation.push_back(D3DXVECTOR2(1, 0));
	moveAnimation.push_back(D3DXVECTOR2(2, 0));
	moveAnimation.push_back(D3DXVECTOR2(3, 0));

	//// Khoi tao animation luc ngoi
	std::vector<D3DXVECTOR2> sitAnimation;
	sitAnimation.push_back(D3DXVECTOR2(4, 0));

	//// Khoi tao animation luc nhay
	std::vector<D3DXVECTOR2> jumpAnimation;
	jumpAnimation.push_back(D3DXVECTOR2(4, 0));

	std::vector<D3DXVECTOR2> deadAnimation;
	deadAnimation.push_back(D3DXVECTOR2(4, 3));

	std::vector<D3DXVECTOR2> invisibleAnimation;
	invisibleAnimation.push_back(D3DXVECTOR2(3, 4));

	std::vector<D3DXVECTOR2> standBack;
	standBack.push_back(D3DXVECTOR2(1, 1));

	// Them cac animation
	anim->AddAnimated(STAND, standAnimation);
	anim->AddAnimated(MOVE, moveAnimation);
	anim->AddAnimated(SIT, sitAnimation);
	anim->AddAnimated(JUMP, jumpAnimation);
	anim->AddAnimated(DEAD, deadAnimation);
	anim->AddAnimated(INVISIBLE, invisibleAnimation);
	anim->AddAnimated(STAND_BACK, standBack);

	action = STAND; //status
}

void Simon::Update(float gameTime) {

	if (velocity.y > 0)
		currentDirection = 1;
	else if (velocity < 0)
		currentDirection = -1;

	if (action != SIT && action != JUMP)
		Enemy::SetBox(30, 0, -15, 0);
	else
		Enemy::SetBox(30, 16, -15, 16);

		if (isGrounded) {
			isInvincible = false;
			canControlKeyboard = false;
			action = DEAD;
			respawnTime += gameTime;
			if (respawnTime > 2) {
				respawnTime = 0.0f;
				isEnable = false;
			}
		}
		else {
			sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime, sprite->GetPosition().y + velocity.y * gameTime);
		}
		anim->DoAnimated(action);
		anim->Update(gameTime);

	//
	if (action == HIT_SIT || action == HIT_STAND || action == HIT_UP_STAIR)
		isFighting = !anim->CheckDoAllFrame();

}

void Simon::Render(ViewPort *viewPort) {
	anim->Render(sprite, isLeft, viewPort);
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

			if (IsKeyDown(DIK_LEFT)) {
				if (action == JUMP && isGrounded == false)
					return;
				isLeft = true;
				if (action != SIT) {
					action = MOVE;
					Move();
				}
			}

			if (IsKeyDown(DIK_RIGHT)) {
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
}

void Simon::KeyBoardHandle(float gameTime) {
	 UpdateKeyboard(gameTime);
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

	if (isInvincible == false) {
		this->CheckColliderWithEnemy(gameTime, listGameObject);
	}
	else {
		invincibleTime -= gameTime;
		if (invincibleTime <= 0) {
			isInvincible = false;
			invincibleTime = INVINCIBLE_TIME;
		}
	}
}

void Simon::CheckColliderWithWall(float gameTime, std::vector<GameObject*>* listGameObject) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++) {
		if ((*i)->GetCollider()->GetTag() == TAG_GROUND) {
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox())) {
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if (timeCollide > 0.0f && timeCollide < 1.0f) {
					if (normalX == 1) {
						sprite->SetPosition(collider->GetBox().left + gameTime * timeCollide * velocity.x - 15 - 0.1, sprite->GetPosition().y);	
						sprite->GetPosition().y;
						return;
					}
					if (normalX == -1) {
						sprite->SetPosition(collider->GetBox().left + gameTime * timeCollide * velocity.x - 15 - 0.1, sprite->GetPosition().y);
						return;
					}
				}
			}
		}
	}
}

void Simon::CheckColliderWithEnemy(float gameTime, std::vector<GameObject*>* listGameObject) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++) {
		if (
			(((*i)->GetCollider()->GetTag() > 0 && (*i)->GetCollider()->GetTag() < 10) || (*i)->GetTag() == 2001 || (*i)->GetTag() == 2000
				|| (*i)->GetCollider()->GetTag() == -3) && (*i)->IsEnable()
		) {
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox())) {
				//
				if (hp > 2)
					hp -= 2;
				else
					hp = 0;
				isGrounded = false;
				isFighting = false;
				break;
			}
			else if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox())) {
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollide > 0.0f && timeCollide < 1.0f)) {
					//
					if (hp > 2)
						hp -= 2;
					else hp = 0;
					isGrounded = false;
					isFighting = false;
					break;
				}
			}
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
				if (normalX == 1) {
					sprite->SetPosition(collider->GetBox().left + gameTime * timeCollide * velocity.x - 15, sprite->GetPosition().y);
				}
				if (normalX == -1) {
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

void Simon::CollideWithDoorHandle(float gameTime, std::vector<GameObject*>* listGameObject, ViewPort *viewPort) {
	CheckColliderWithDoor(gameTime, listGameObject);
	if (doorCollideDirection == -1 && !door->IsOccurred()) {
		if (viewPort->GetCameraPosition().x + GAME_WIDTH / 2 < collideDoor.x) {
			isGoingThrowDoor = true;
			Stand();
			canControlKeyboard = false;
			viewPort->SetCameraPosition(viewPort->GetCameraPosition().x + 120 * gameTime, viewPort->GetCameraPosition().y);
		}
		else {
			door->isLeft = isLeft;
			door->SetSpriteXPosition(30);
			viewPort->SetCameraPosition(viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y);

			if (!door->IsDoAllFrame()) {
				door->SetDrawable(true);
				door->UpdateAnim(gameTime);
			}
			else {
				if (sprite->GetPosition().x < collideDoor.x + 110) {
					action = MOVE;
					SetPosition(GetPosition().x + 75 * gameTime, GetPosition().y);
				}
				else {
					Stand();
					door->SetAction(1);

					if (!door->IsDoAllFrame()) {
						door->UpdateAnim(gameTime);
					}
					else {
						door->SetDrawable(false);
						if (viewPort->GetCameraPosition().x < collideDoor.x + 16)
							viewPort->SetCameraPosition(viewPort->GetCameraPosition().x + 120 * gameTime, viewPort->GetCameraPosition().y);
						canControlKeyboard = true;
						doorCollideDirection = 0;
						door->SetIsOccurred(true);
						isGoingThrowDoor = false;
					}
				}
			}
		}
	}
	else if (doorCollideDirection == 1 && !door->IsOccurred()) {
		if (viewPort->GetCameraPosition().x + GAME_WIDTH / 2 > collideDoor.x) {
			isGoingThrowDoor = true;
			Stand();
			canControlKeyboard = false;
			viewPort->SetCameraPosition(viewPort->GetCameraPosition().x - 120 * gameTime, viewPort->GetCameraPosition().y);
		}
		else {
			door->isLeft = isLeft;
			door->SetSpriteXPosition(-30);
			viewPort->SetCameraPosition(viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y);
			if (!door->IsDoAllFrame()) {
				door->UpdateAnim(gameTime);
				door->SetDrawable(true);
			}
			else {
				if (sprite->GetPosition().x > collideDoor.x - 120) {
					action = MOVE;
					SetPosition(GetPosition().x - 75 * gameTime, GetPosition().y);
				}
				else {
					Stand();
					door->SetAction(MOVE);
					if (!door->IsDoAllFrame()) {
						door->UpdateAnim(gameTime);
						//
					}
					else {
						door->SetDrawable(false);
						if (viewPort->GetCameraPosition().x + GAME_WIDTH > collideDoor.x - 2)
							viewPort->SetCameraPosition(viewPort->GetCameraPosition().x - 120 * gameTime, viewPort->GetCameraPosition().y);
						else {
							viewPort->SetCameraPosition(viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y);
							canControlKeyboard = true;
							doorCollideDirection = 0;
							door->SetIsOccurred(true);
							isGoingThrowDoor = false;
						}
					}
				}
			}
		}
	}
}

bool Simon::IsColliderWithCheckPoint(float gameTime, std::vector<GameObject*>* listGameObject) {
	float normalX = 0;
	float normalY = 0;
	float timeCollide;
	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++) {
		if ((*i)->GetCollider()->GetTag() == TAG_CHECK_POINT) {
			Box tempBox = (*i)->GetCollider()->GetBox();
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox())) {
				return true;
			}
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox())) {
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollide >= 0.0f && timeCollide < 1.0f)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Simon::IsColliderWith(float gameTime, GameObject * object) {
	return Enemy::IsColliderWith(gameTime, object);
}