#pragma once
#include "GameObject.h"
#include "Animated.h"


#define OPENING_DOOR 0
#define CLOSING_DOOR 1

class Door : public GameObject
{
public:
	Door();
	~Door();

	bool isLeft;
	bool setedDoAllFrame;
	int doorAction;

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	void Render(ViewPort *viewPort);
	void Update(float gameTime);

	void DoAnim();
	void UpdateAnim(float gameTime);
	int GetAction() { return doorAction; };
	void SetAction(int action) {
		if (!setedDoAllFrame)
			anim->SetDoAllFrame(false);
		setedDoAllFrame = true;
		doorAction = action;
	}

	bool IsDoAllFrame() { return anim->CheckDoAllFrame(); };
	void SetDrawable(bool status) { isDrawable = status; };
	void SetSpriteXPosition(int x);

	bool IsOccurred() { return isOccurred; };
	void SetIsOccurred(bool status) { isOccurred = status; };

private:
	bool isOccurred; //co` de biet simon di qua canh cua chua

	void InitAnim();
	Sprite* spriteDoorAnim;
	Animated *anim;

	bool isDrawable;
	bool isSetPositionAnim;

};

//Door::Door()
//{
//}
//
//Door::~Door()
//{
//}