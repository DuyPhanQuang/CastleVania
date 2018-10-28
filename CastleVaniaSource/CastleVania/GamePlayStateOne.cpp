#include "GamePlayStateOne.h"

GamePlayStateOne::GamePlayStateOne() {}
GamePlayStateOne::~GamePlayStateOne() {}

bool GamePlayStateOne::Initialize(Graphics *graphics) {
	this->gDevice = graphics->GetDevice();
	viewPort = new ViewPort(0, GAME_HEIGHT);
	sprite = new Sprite();
	if (!sprite->Initialize(gDevice, LEVEL_ONE_BG))
		return false;
	castleSprite = new Sprite(1408, 347);
	if (!castleSprite->Initialize(gDevice, CASTLE_SPRITE))
		return false;
	tileMap = new TileMap(1536, 392, sprite, 64, 64);
	tileMap->LoadListTileFromFile(LEVEL_ONE_MATRIX_BG);

	cameraObject = new GameObject();
	cameraObject->Initialize(gDevice, SIMON_SPRITE, viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y, 5);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(gDevice, GROUND, viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y, TAG_GROUND);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(gDevice, GROUND, viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y, TAG_GROUND);

	list = new std::vector<GameObject*>();

	simon->SetPosition(100, 150);
	simon->Reload();

	changeState = false;
	time = 0;
	return true;
}

void GamePlayStateOne::Update(float gameTime) {
	time += gameTime;
	if (simon->GetPosition().x >= GAME_HEIGHT / 2 && simon->GetPosition().x <= 1536 - GAME_WIDTH / 2 - 32) {
		D3DXVECTOR3 currentCamera = viewPort->GetCameraPosition(); //lay pos hien tai cua camera
		currentCamera.x += simon->GetVelocity().x * gameTime;
		viewPort->SetCameraPosition(currentCamera.x, currentCamera.y); //update lai pos camera
	}

	cameraObject->SetPosition(viewPort->GetCameraPosition());
	// handle truong hop de cho simon luon o trong camera
	leftCamera->SetPosition(viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y);
	leftCamera->SetBox(leftCamera->GetPosition().x, leftCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	rightCamera->SetPosition(viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y);
	rightCamera->SetBox(rightCamera->GetPosition().x, rightCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	list->clear();

	simon->KeyBoardHandle(gameTime);
	simon->Update(gameTime);
	simon->CheckCollider(gameTime, list);
	simon->CheckColliderWith(gameTime, leftCamera);
	simon->CheckColliderWith(gameTime, rightCamera);

	if (IsKeyPress(DIK_M))
		SetChangingState(true);

	//den vi tri de chuyen scene(stage)
	if (simon->GetPosition().x > 1300 && simon->GetPosition().x < 1400) {
		simon->SetVelocity(D3DXVECTOR3(0, 0, 0));
		simon->SetPosition(simon->GetPosition().x + 50 * gameTime, simon->GetPosition().y);
		simon->SetAction(1);
		simon->SetCanControlKeyboard(false);
	}
	else if (simon->GetPosition().x > 1400) {
		SetChangingState(true);
	}
}

void GamePlayStateOne::Render() {
	tileMap->Draw(viewPort);
	for (auto i = list->begin(); i != list->end(); i++) {
		(*i)->isAdded = false;
		(*i)->Render(viewPort);
	}
	simon->Render(viewPort);
	castleSprite->Render(viewPort);
}

bool GamePlayStateOne::GetChangingState() {
	return GameState::GetChangingState();
}

void GamePlayStateOne::SetChangingState(bool status) {
	GameState::SetChangingState(status);
}

void GamePlayStateOne::DestroyAll() {
	delete(tileMap);
	delete(ground);
	delete(cameraObject);
	delete(viewPort);
}