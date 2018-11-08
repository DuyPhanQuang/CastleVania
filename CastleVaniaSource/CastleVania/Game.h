#pragma once
#ifndef GAME_H
#define GAME_H
#include "Graphics.h"
#include "ViewPort.h"
#include "Input.h"
#include "Simon.h"
#include "GameTime.h"
#include "GSprite.h"
#include "Input.h"
#include "ScreenManager.h"

class Game
{
public:
	Game();
	~Game();

	bool Initialize(HWND hWnd, int width, int height);
	void Run(); //de mai mot dung goi update va draw
	void Update(float _gameTime);
	void Draw();

private:
	Graphics* gDevice;
	ViewPort* viewPort;

	DWORD timeStart;
	DWORD timeNow;
	//float gameTime;
	GameTime* gameTime;

	ScreenManager* screenManager;
};

//Game::Game()
//{
//}
//
//Game::~Game()
//{
//}
#endif // !GAME_H
