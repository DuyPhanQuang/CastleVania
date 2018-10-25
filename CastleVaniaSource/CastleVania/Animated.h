#pragma once

#ifndef ANIMATED_H
#define ANIMATED_H

#include "GSprite.h"
#include <vector>
#include <map>

class Animated
{
public:
	Animated();
	~Animated();
	float frameWidth; //chieu dai cua frame
	float frameHeight; // chieu rong cua frame
	float frameTime; //thoi gian giua 2 frame tu anim

	bool Initialize(Sprite *sprite, float frameWidth, float frameHeight, float frameTime);

	void Update(float gameTime);

	//nhap mot vector bao gom cac toa do theo hang va cot de dua no vao lAnimated
	void AddAnimated(int animId, std::vector<D3DXVECTOR2> animated);

	//ve frame moi chi so frame
	void Render(Sprite *sprite, bool isLeft, ViewPort *viewPort);

	void DoAnimated(int animId);
	bool CheckDoAllFrame() { return isDoAllFrame; };
	int GetCurrentFrame() { return currentFrame; };
	void GetCurrentFrame(bool status) { isDoAllFrame = status; };

private:
	
	float timeDelay;

	RECT rect; //thay doi frame giua anim

	//lAnimated ---vector chua cac vector anim,
	//lAnimated.size();
	std::map<int, std::vector<D3DXVECTOR2>> lAnimated;

	//frame se dc hien thi
	int currentFrame;

	//animation hien tai dang su dung
	int currentAnimated;
	bool isChangeAnim;
	bool isChanged;
	bool isDoAllFrame;
};

//Animated::Animated()
//{
//}
//
//Animated::~Animated()
//{
//}

#endif // !ANIMATED_H

