#include "Game.h"
#include "Input.h"
#include "ScreenManager.h"

Game::Game() {
	gDevice = NULL;
	gameTime = NULL;
}

bool Game::Initialize(HWND hWnd, int width, int height) {
	if (!InitDirectInput() || !InitKeyboard(hWnd))
		return false;

	gameTime = new GameTime();
	if (!gameTime->Initialize())
		return false;

	screenManager = new ScreenManager();

	if (!screenManager->Initialize(hWnd))
		return false;
	screenManager->LoadState(GAME_INTRO_SCENE);
	
	return true;
}

void Game::Run() {
	gameTime->Update();

	Update(gameTime->m_elapsedGameTime);
	Draw();
}

void Game::Update(float _gameTime) {
	PollKeyboard();
	screenManager->Update(_gameTime);
}

void Game::Draw() {
	screenManager->Render();
}

Game::~Game() {
	SAFE_DELETE(gDevice);
	SAFE_DELETE(viewPort);
	SAFE_DELETE(gameTime);
}