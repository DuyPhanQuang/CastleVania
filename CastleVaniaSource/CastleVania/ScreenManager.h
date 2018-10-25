#pragma once
#include "Graphics.h"
#include "Input.h"
#include "GamePlayStateOne.h"
#include "IntroScene.h"
	
class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	bool Initialize(HWND hwnd);
	void LoadState(int stateID);
	void NextStateLevel();
	void Render();
	void Update(float gameTime);

private:
	Graphics* gDevice;
	GameState* gameState;
	int stateID; // CO` DE CHUYEN STAGE
};

//ScreenManager::ScreenManager()
//{
//}
//
//ScreenManager::~ScreenManager()
//{
//}