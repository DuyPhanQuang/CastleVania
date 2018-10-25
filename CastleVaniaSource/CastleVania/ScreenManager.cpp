#include "ScreenManager.h"

//chuyen cac thanh phan tu game.cpp sang

ScreenManager::ScreenManager(){}
ScreenManager::~ScreenManager(){}

bool ScreenManager::Initialize(HWND hwnd) {
	gDevice = new Graphics();
	if (!gDevice->Init(hwnd))
		return false;
	return true;
}

//load state
void ScreenManager::LoadState(int stateID) {
	switch (stateID) {
	case GAME_INTRO_SCENE:
		gameState = new IntroScene();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case GAME_PLAY_STATE_ONE:
		delete(gameState);
		gameState = new GamePlayStateOne();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	default:
		break;
	}
}

void ScreenManager::Render() {
	gDevice->Clear();
	gDevice->Begin();

	gameState->Render();
	gDevice->End();
	gDevice->Present();
}

void ScreenManager::NextStateLevel() {
	stateID++;
}

void ScreenManager::Update(float gameTime) {
	if (gameState->GetChangingState()) {
		if (stateID != GAME_MENU_STATE) {
			gameState->DestroyAll();
		}
		NextStateLevel();
		LoadState(stateID);
		gameState->SetChangingState(false);
	}

	gameState->Update(gameTime);
}