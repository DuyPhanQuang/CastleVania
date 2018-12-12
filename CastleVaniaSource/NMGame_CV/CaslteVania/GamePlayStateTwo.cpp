#include "GamePlayStateTwo.h"



GamePlayStateTwo::GamePlayStateTwo()
{
}


GamePlayStateTwo::~GamePlayStateTwo()
{
}

bool GamePlayStateTwo::Initialize(Graphics *graphics)
{
	this->graphics = graphics;
	this->gDevice = graphics->GetDevice();

	timeKillAll = 0;
	choose = false;

	simon->SetCanControlKeyboard(true);

	viewPort = new ViewPort(0, GAME_HEIGHT + 370);

	sprite = new Sprite();
	if (!sprite->Initialize(gDevice, LEVEL_TWO_BG))
		return false;

	tileMap = new TileMap(5632, 768, sprite, 64, 64);
	tileMap->LoadListTileFromFile(LEVEL_TWO_MATRIX_BG);

	cameraObject = new GameObject();
	cameraObject->Initialize(gDevice, SIMON_SPRITE, viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y, 5);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\0.png", viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y, TAG_GROUND);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\0.png", viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y, TAG_GROUND);

	quadTree = new QuadTree(gDevice, viewPort);
	quadTree->Load("Resource\\sprites\\QuadTree\\level2.txt");

	list = new std::vector<GameObject*>();

	//simon = staticSimon; 5, 600
	simon->SetPosition(5, 600);
	simon->Reload();

	#pragma region Init enemy 

	listEnemy = new std::vector<GameObject*>();
	InitZombie(gDevice);
	InitPanther(gDevice);

	#pragma endregion

	RECT *area = new RECT();
	*area = { (LONG)viewPort->GetCameraPosition().x + 5600 - GAME_WIDTH, (LONG)viewPort->GetCameraPosition().y - 116, (LONG)viewPort->GetCameraPosition().x + 5600, (LONG)viewPort->GetCameraPosition().y - 240 };

	changeState = false;
	inBoss = false;

	Item::TakeSimonPointer(simon);
	Item::TakeListEnemyPointer(listEnemy);
	listItem = new std::vector<Item*>();


	ui = new UI();
	ui->Initialize(gDevice, simon, 0);
	time = 500;
	score = 0;

	return true;
}

void GamePlayStateTwo::Update(float gameTime)
{
	GameState::Update(gameTime);

	time -= gameTime;
	ui->Update(0, (int)time, 3, 1);

	#pragma region Init cameraObject, left camera, right camera

	cameraObject->SetPosition(viewPort->GetCameraPosition());
	cameraObject->SetRegion(0, GAME_WIDTH, 0, -GAME_HEIGHT);

	//khong cho simon di ra khoi camera
	leftCamera->SetPosition(viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y);
	leftCamera->SetBox(leftCamera->GetPosition().x, leftCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	rightCamera->SetPosition(viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y);
	rightCamera->SetBox(rightCamera->GetPosition().x, rightCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

#pragma endregion

	//////////////////////////////////--------- LIST ITEM ---------///////////////////////////////////////
	// * list = list of object, include [ground, candle, ...]
	// * listItem = list of drop item

	list->clear();
	quadTree->GetObjectList(list, cameraObject->GetRegion());

	for (auto i = list->begin(); i != list->end(); i++)
	{
		if (!(*i)->IsEnable())
		{
			// Drop item from hitting object
			if ((*i)->isDropItem == false)
			{
				Item *item = new Item();
				item->Initialize(gDevice, (*i)->GetPosition().x, (*i)->GetPosition().y);
				//item->Initialize(gDevice, (*i)->GetPosition().x, (*i)->GetPosition().y, ITEM_ROSARY, 10);
				listItem->push_back(item);
				(*i)->isDropItem = true;
			}
			quadTree->Remove((*i));
		}
		else
		{
			if ((*i)->GetTag() == TAG_DOOR && (*i)->GetID() == 1256)
				((Door*)(*i))->SetIsOccurred(true);
			(*i)->Update(gameTime);
		}
	}

	for (auto i = listItem->begin(); i != listItem->end(); i++)
	{
		(*i)->Update(gameTime);
		(*i)->CheckCollider(gameTime, list);
	}

	//end lisitem


	listEnemy->clear();

	#pragma region Check if simon is going throw the door dont let any object update

	if (!simon->IsGoingThrowDoor())
	{
		UpdateZombie(gameTime);
		UpdatePanther(gameTime);
	}

#pragma endregion

	CheckPointHandle(gameTime, simon, list);

	simon->KeyBoardHandle(gameTime);
	simon->Update(gameTime);

	CameraFollowHandle(gameTime);

	simon->CheckCollider(gameTime, list);
	simon->CheckColliderWith(gameTime, leftCamera);
	simon->CheckColliderWith(gameTime, rightCamera);
	simon->CollideWithDoorHandle(gameTime, list, viewPort);

	for (int i = 0; i < simon->GetNoSubWeapon();i++)
	{
		if (simon->subWeapon[i]->GetTag() == TAG_CROSS && !simon->subWeapon[i]->IsEnable())
			((Cross*)(simon->subWeapon[i]))->SetDefaultProperties();
		
		simon->subWeapon[i]->CheckCollider(gameTime, list);

		if (simon->subWeapon[i]->GetPosition().x < viewPort->GetCameraPosition().x ||
			simon->subWeapon[i]->GetPosition().x > viewPort->GetCameraPosition().x + GAME_WIDTH)
			simon->subWeapon[i]->SetEnable(false);

		if (simon->subWeapon[i]->GetTag() == TAG_CROSS)
		{
			((Cross*)(simon->subWeapon[i]))->CheckTurnBack(gameTime, viewPort);
			if (simon->subWeapon[i]->CheckColliderWith(gameTime, simon) && ((Cross*)(simon->subWeapon[i]))->IsTurnBack())
				simon->subWeapon[i]->SetEnable(false);
		}
		
	}

	if (time < 0)
	{
		simon->SetEnable(false);
		time = 500;
	}

	if (simon->GetHP() <= 0 && inBoss) {
		inBoss = false;
	}

	if (simon->GetPosition().y < viewPort->GetCameraPosition().y - GAME_HEIGHT)
		simon->SetHP(0);

	if (IsKeyPress(DIK_M))
		SetChangingState(true);
}

	#pragma region Init enemies

void GamePlayStateTwo::InitZombie(LPDIRECT3DDEVICE9 gDevice)
{
	//Init zombie
	for (int i = 0; i < 3; i++)
	{
		zombies[i] = new Zombie(1, 2, 100);
		zombies[i]->Initialize(gDevice, ZOMBIE_SPRITE, GAME_WIDTH + (i + 1) * 100, 510, TAG_ZOMBIE);
		zombies[i]->SetEnable(true);
	}
}

void GamePlayStateTwo::InitPanther(LPDIRECT3DDEVICE9 gDevice)
{
	//Init panther
	for (int i = 0; i < 3; i++)
	{
		panther[i] = new Panther(1, 2, 150);
		panther[i]->Initialize(gDevice, PANTHER_SPRITE, 1400 + i * 300, 800, TAG_PANTHER);
		panther[i]->SetEnable(true);
	}

	//Set lai position cho panther
	panther[0]->SetPosition(1700, 646);
	panther[1]->SetPosition(1400, 578);
	panther[2]->SetPosition(1900, 578);
}

	#pragma endregion

	#pragma region Update enemies

void GamePlayStateTwo::UpdateZombie(float gameTime)
{
		//neu nhu simon di vao vung hoat dong cua zombie
		if ((simon->GetPosition().x > 0 && simon->GetPosition().x < 890)
			|| (simon->GetPosition().x > 2220 && simon->GetPosition().x < 2950)
			|| (simon->GetPosition().x > 4125 && simon->GetPosition().x < 4950))
		{
			for (int i = 0; i < 3; i++)
			{
				//neu zombie disable va thoi gian ngu cua no lon hon 1
				if (!zombies[i]->IsEnable() && zombies[i]->respawnTime > 1.0f)
				{
					//neu simon nam trong vai vung dac biet thi cho no di chuyen tu trai qua
					if ((simon->GetPosition().x > 0 && simon->GetPosition().x < 630)
						|| (simon->GetPosition().x > 2220 && simon->GetPosition().x < 2700)
						|| (simon->GetPosition().x > 4125 && simon->GetPosition().x < 4870))
					{
						zombies[i]->SetPosition(viewPort->GetCameraPosition().x + GAME_WIDTH - 1, simon->GetPosition().y);
						zombies[i]->SetIsLeft(true);
					}
					else
					{
						zombies[i]->SetPosition(viewPort->GetCameraPosition().x + 1, simon->GetPosition().y);
						zombies[i]->SetIsLeft(false);
					}

					zombies[i]->SetEnable(true);
					zombies[i]->Respawn();

					//doi thoi gian cua cac zombie sau con zombie trc 1 thoi khoang thoi gian
					if (i == 0)
					{
						zombies[1]->respawnTime = 0.5f;
						zombies[2]->respawnTime = 0.5f;
					}

					if (i == 1)
						zombies[2]->respawnTime = 0.5f;
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			//neu zombie khong nam trong camera thi disable
			if (!IsInCamera(zombies[i]->GetPosition().x, zombies[i]->GetPosition().y))
				zombies[i]->SetEnable(false);

			zombies[i]->Update(gameTime);
			zombies[i]->CheckCollider(gameTime, list);

			//neu zombie enable thi update va dua vao list
			if (zombies[i]->IsEnable())
			{
				list->push_back(zombies[i]);
				listEnemy->push_back(zombies[i]);
			}
		}
}

	void GamePlayStateTwo::UpdatePanther(float gameTime)
	{
		//update and check collision for panther and add panther to list collision
		for (int i = 0; i < sizeof(panther) / sizeof(*panther); i++)
		{
			//neu nhu panther di ra khoi camera va simon dang trong vung hoat dong cua no
			//thi enable = false
			if (!IsInCamera(panther[i]->GetPosition().x, panther[i]->GetPosition().y)
				&& (simon->GetPosition().x < 2100 && simon->GetPosition().x > 1100) && panther[i]->GetAction() != SIT)
			{
				panther[i]->SetEnable(false);
			}

			//neu camera o ngoai vung hoat dong cua no thi dua no ve vi tri cu va enable = true
			if (viewPort->GetCameraPosition().x > 2100 || viewPort->GetCameraPosition().x < 740)
			{
				panther[i]->SetEnable(true);
				panther[i]->SetHP(1);
				panther[i]->SetAction(SIT);
				if (i == 0)
					panther[0]->SetPosition(1700, 646);
				else if (i == 1)
					panther[1]->SetPosition(1400, 578);
				else
					panther[2]->SetPosition(1900, 578);
				//panther[i]->Respawn();
				panther[i]->SetIsLeft(!simon->GetIsLeft());
			}

			//neu simon di lai gan panther thi cho panther di chuyen
			if ((abs(simon->GetPosition().x - panther[i]->GetPosition().x) < 120) && panther[i]->GetAction() == SIT)
			{
				panther[i]->SetAction(MOVE);
			}

			//neu panther nam trong camera va no enable thi update va dua vao list de check collider
			if (IsInCamera(panther[i]->GetPosition().x, panther[i]->GetPosition().y) && panther[i]->IsEnable())
			{
				panther[i]->Update(gameTime);
				panther[i]->CheckCollider(gameTime, list);
				list->push_back(panther[i]);
				listEnemy->push_back(panther[i]);
			}
		}
	}


	#pragma endregion

void GamePlayStateTwo::Render()
{
	tileMap->Draw(viewPort);
	for (auto i = list->begin(); i != list->end(); i++)
	{
		(*i)->isAdded = false;
		(*i)->Render(viewPort);
	}
	for (auto i = listItem->begin(); i != listItem->end(); i++)
	{
		(*i)->Render(viewPort);
	}

	simon->Render(viewPort);
	ui->Render();
}

bool GamePlayStateTwo::GetChangingState()
{
	return GameState::GetChangingState();
}

void GamePlayStateTwo::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

	#pragma region camera handle

bool GamePlayStateTwo::CameraFollowHandle(float gameTime)
{
	if (simon->nextStage)
	{
		SetChangingState(true);
		simon->nextStage = false;
	}
	
	if (simon->GetPosition().x >= GAME_WIDTH / 2 && simon->GetPosition().x < 3078 - GAME_WIDTH / 2)
	{
		D3DXVECTOR3 currentCamera = viewPort->GetCameraPosition();
		currentCamera.x = simon->GetPosition().x - GAME_WIDTH / 2;
		viewPort->SetCameraPosition(currentCamera.x, currentCamera.y);
	}
	else if (simon->GetPosition().x >= 3078 && simon->GetPosition().x < 4096 - GAME_WIDTH / 2)
	{
		D3DXVECTOR3 currentCamera = viewPort->GetCameraPosition();
		if (simon->GetPosition().x >= 3078 + GAME_WIDTH / 2 && simon->GetPosition().x <= 4096 - GAME_WIDTH / 2)
			currentCamera.x = simon->GetPosition().x - GAME_WIDTH / 2;
		viewPort->SetCameraPosition(currentCamera.x, currentCamera.y);
	}
	else if (simon->GetPosition().x >= 4096 && simon->GetPosition().x <= 5662 - GAME_WIDTH / 2)
	{
		{
			if (viewPort->GetCameraPosition().x + GAME_WIDTH < 5662 - 32)
			{
				if (simon->GetPosition().x >= 4096 + GAME_WIDTH / 2 && simon->GetPosition().x <= 5662 - GAME_WIDTH / 2)
				{
					D3DXVECTOR3 currentCamera = viewPort->GetCameraPosition();
					currentCamera.x = simon->GetPosition().x - GAME_WIDTH / 2;
					viewPort->SetCameraPosition(currentCamera.x, currentCamera.y);
				}
			}
			else
			{
				// Do something here
				inBoss = true;
			}
		}
	}


	return false;
}

bool GamePlayStateTwo::IsInCamera(float x, float y)
{
		return (x > viewPort->GetCameraPosition().x
			&& x < viewPort->GetCameraPosition().x + GAME_WIDTH
			&& y < viewPort->GetCameraPosition().y
			&& y > viewPort->GetCameraPosition().y - GAME_HEIGHT);
}

	#pragma endregion

void GamePlayStateTwo::DestroyAll()
{
	//delete(simon);
	delete(tileMap);
	delete(ground);
	delete(cameraObject);
	delete(listObject);
	delete(viewPort);
	delete(listItem);
	delete(list);
}