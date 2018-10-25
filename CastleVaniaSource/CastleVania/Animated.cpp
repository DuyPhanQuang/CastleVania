#include "Animated.h"

Animated::Animated() {
	timeDelay = 0.0f;
	isDoAllFrame = false;
};
Animated::~Animated() {}

bool Animated::Initialize(Sprite *sprite, float _frameWidth, float _frameHeight, float _frameTime) {
	frameTime = _frameTime;
	frameWidth = _frameWidth;
	frameHeight = _frameHeight;

	//chinh lai mau cho simon, sau nay an item se doi mau
	sprite->setColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	//SET CURRENT FRAME lam frame dau tien tu animated
	currentFrame = 0;

	//dat anim hien tai = 0;
	currentAnimated = 0;

	isChangeAnim = false;
	isChanged = false;

	return TRUE;
}

void Animated::AddAnimated(int animId, std::vector<D3DXVECTOR2> animated) {
	lAnimated[animId] = animated;
}

void Animated::Update(float gameTime) {
	isDoAllFrame = false;

	//dua rect toi vi tri can ve
	D3DXVECTOR2 frame = lAnimated[currentAnimated][currentFrame];
	rect.top = frameHeight * frame.y;
	rect.left = frameWidth * frame.x;
	rect.bottom = frameHeight * (frame.y + 1);
	rect.right = frameWidth * (frame.x + 1);

	//update to get elapsed time
	timeDelay += gameTime;
	if (isChangeAnim) {
		timeDelay = gameTime;
		D3DXVECTOR2 frame = lAnimated[currentAnimated][currentFrame];
		rect.top = frameHeight * frame.y;
		rect.left = frameWidth * frame.x;
		rect.bottom = frameHeight * (frame.y + 1);
		rect.right = frameWidth * (frame.x + 1);
	}
	//neu tong tg lon hon hoac bang tg giua 2 frame thi thay doi frame
	else if (timeDelay >= frameTime) {
		//change next frame
		//neu ko co next frame thi return lai first frame
		currentFrame++;
		if (currentFrame >= lAnimated[currentAnimated].size()) {
			currentFrame = 0;
			isDoAllFrame = false;
		}

		//reset total time
		timeDelay = 0.0f;
	}
}

void Animated::Render(Sprite *sprite, bool isLeft, ViewPort *viewPort) {
	sprite->Render(rect, isLeft, frameWidth, frameHeight, viewPort);
}

void Animated::DoAnimated(int animId) {
	//dua frame tro ve frame dau tien cua anima moi
	if (currentAnimated != animId) {
		currentFrame = 0;
		currentAnimated = animId;
		isChangeAnim = TRUE;
	}
	else {
		isChangeAnim = FALSE;
	}
}