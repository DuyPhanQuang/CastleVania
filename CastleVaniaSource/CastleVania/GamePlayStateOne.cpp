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
	cameraObject->Initialize(gDevice, SIMON_SPRITE, viewPort->GetCameraPosition.x, viewPort->GetCameraPosition.y, 5);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(gDevice, GROUND, viewPort->GetCameraPosition.x, viewPort->GetCameraPosition.y, TAG_GROUND);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(gDevice, GROUND, viewPort->GetCameraPosition.x + GAME_WIDTH, viewPort->GetCameraPosition.y, TAG_GROUND);

	list = new std::vector<GameObject*>();

	changeState = false;
	time = 0;
	return true;
}

void GamePlayStateOne::Render() {
	tileMap->Draw(viewPort);
	for (auto i = list->begin(); i != list->end(); i++) {
		(*i)->isAdded = false;
		(*i)->Render(viewPort);
	}
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