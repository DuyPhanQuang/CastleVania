#pragma once
#include "Graphics.h"
#include "Input.h"
#include "GameState.h"
	
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
	int stateID;
};

//ScreenManager::ScreenManager()
//{
//}
//
//ScreenManager::~ScreenManager()
//{
//}