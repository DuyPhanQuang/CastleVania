#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "QuadTree.h"
#include "Ground.h"
#include "LargeCandle.h"
#include "Zombie.h"
#include "Panther.h"
#include "UI.h"
#include "Bat.h"

class GamePlayStateTwo : public GameState
{
private:
	//Simon *simon;
	TileMap *tileMap;
	Sprite *sprite;
	GameObject *ground;
	GameObject *cameraObject;
	Zombie *zombies[3];
	Panther *panther[3];
	Bat *bat;
	GameObject *leftCamera;
	GameObject *rightCamera;

	QuadTree *quadTree;
	UI *ui;

	bool inBoss;

	std::vector<GameObject*> *list;
	std::vector<Item*> *listItem;
	std::vector <GameObject*> *listEnemy;

	LPDIRECT3DDEVICE9 gDevice;
public:
	GamePlayStateTwo();
	~GamePlayStateTwo();
	bool Initialize(Graphics *graphics);
	void Render();
	void Update(float gameTime);
	void DestroyAll();
	/*
	* Overload tu class cha
	* Set va get gia tri cua $changeState
	*/

	bool IsInCamera(float x, float y);

	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime);

	void InitZombie(LPDIRECT3DDEVICE9 gDevice);
	void InitPanther(LPDIRECT3DDEVICE9 gDevice);

	void UpdateZombie(float gameTime);
	void UpdatePanther(float gameTime);
};

