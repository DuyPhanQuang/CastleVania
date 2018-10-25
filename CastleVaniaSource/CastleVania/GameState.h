#pragma once

#ifndef GAMESTATE_H

#include "ViewPort.h"
#include <fstream>
#include <vector>
#include "Graphics.h"
#include "Simon.h"

static int score;

class GameState {
	float simonDeadTime = 1.5;
protected:
	ViewPort* viewPort;
	std::vector<GameObject*> *listObject;
	static Simon* simon;
	Graphics *graphics;

	D3DXVECTOR3 simonCheckPoint;
	D3DXVECTOR3 cameraCheckPoint;
	float time;
	float timeKillAll;
	bool choose;
	bool changeState;
public:
	int state;
	GameState() {}
	~GameState() {}
	//
	virtual bool Initialize(Graphics *graphics) = 0;
	virtual void Render() {};
	virtual void Update(float gameTime);
	virtual void DestroyAll() = 0;

	//get-set de chuyen screen
	virtual bool GetChangingState() { return changeState; };
	virtual void SetChangingState(bool status) { changeState = status; }

	virtual bool CameraFollowHandle(float gameTime) = 0;

	//handle chuyen scene 2
};

#endif // !GAMESTATE_H

