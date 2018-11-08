#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Ground.h"

class GamePlayStateOne : public GameState
{
public:
	GamePlayStateOne();
	~GamePlayStateOne();
	bool Initialize(Graphics *graphics);
	void Render();
	void Update(float gameTime);
	void DestroyAll();

	//overload tu parent class
	//get set cac gia tri cua changeState
	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime) { return true; }


private:
	TileMap *tileMap;
	Sprite *sprite;
	Sprite *castleSprite;
	
	GameObject *ground;
	GameObject *cameraObject;
	GameObject *leftCamera;
	GameObject *rightCamera;


	LPDIRECT3DDEVICE9 gDevice;
	std::vector<GameObject*> *list;
};

//GamePlayStateOne::GamePlayStateOne()
//{
//}
//
//GamePlayStateOne::~GamePlayStateOne()
//{
//}
