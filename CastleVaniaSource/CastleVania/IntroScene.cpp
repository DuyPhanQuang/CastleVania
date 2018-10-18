#include "IntroScene.h"

IntroScene::IntroScene() {}

IntroScene::~IntroScene() {}

bool IntroScene::Initialize(Graphics *graphics) {
	this->gDevice = graphics->GetDevice();
	timeDelay = 0;
	viewPort = new ViewPort(0, GAME_HEIGHT);
	sprite = new Sprite();
	if (!sprite->Initialize(gDevice, INTRO_SCENE_BG))
		return false;

	helicopter = new Sprite();
	if (!helicopter->Initialize(gDevice, HELICOPTER_SPRITE))
		return false;
	helicopter->SetPosition(552, 350);

	ground = new Ground(640, 32);
	ground->Initialize(gDevice, NULL_SPRITE, 0, 16, TAG_GROUND);
	tileMap = new TileMap(640, 448, sprite, 64, 64);
	tileMap->LoadListTileFromFile(INTRO_SCENE_MATRIX_BG);

	changeState = false;

	simon = new Simon(8, 0, 0);
	if (!simon->Initialize(gDevice, SIMON_SPRITE, 610, 91, TAG_SIMON))
		return false;
	simon->SetIsLeft(true);

	return true;
}

void IntroScene::Render() {
	tileMap->Draw(viewPort);
	ground->Render(viewPort);

	helicopter->Render(viewPort);
	simon->Render(viewPort);
}