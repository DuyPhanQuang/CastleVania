#pragma once

#ifndef _GAMESTATE_H_
#define __GAMESTATE_H__

#include "ViewPort.h"
#include <fstream>
#include <vector>
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
	virtual void SetChangingState(bool status) { changeState = status; };

	virtual bool CameraFollowHandle(float gameTime) = 0;

	void CheckPointHandle(float gameTime, Simon* simon, std::vector<GameObject*> *list) {
		if (simon->IsColliderWithCheckPoint(gameTime, list)) {
			simonCheckPoint = simon->GetPosition();
			cameraCheckPoint = viewPort->GetCameraPosition();
		}

		if (simon->GetPosition().y < viewPort->GetCameraPosition().y - GAME_HEIGHT) {
			simon->Reset(simonCheckPoint);
			viewPort->SetCameraPosition(cameraCheckPoint.x, cameraCheckPoint.y);
		}

		if (!simon->IsEnable()) {
			simon->Reset(simonCheckPoint);
			viewPort->SetCameraPosition(cameraCheckPoint.x, cameraCheckPoint.y);
		}
		//else {
		//	simon->Reset(simonCheckPoint);
		//	viewPort->SetCameraPosition(cameraCheckPoint.x, cameraCheckPoint.y);
		//}
	}
};

#endif _GAMESTATE_H_

