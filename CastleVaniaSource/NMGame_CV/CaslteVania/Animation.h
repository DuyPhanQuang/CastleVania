#ifndef ANIMATION_H
#define ANIMATION_H


#include "Sprite.h"
#include <vector>
#include <map>

class Animation
{
private:
	float		timeDelay;
	
	RECT		rect;			// Change frame between animation

								// Vector chua cac vector animation, viet tat cua list animation
								// lAnimation.size() la so luong animation dung trong class nyy
								//std::vector< std::vector<D3DXVECTOR2> > lAnimation;
	std::map<int, std::vector<D3DXVECTOR2> > lAnimation;

	// frame dang dc hien thi
	int currentFrame;

	// Animation hien tai dang su dung
	int currentAnimation;

	bool isChangeAnim;

	bool isChanged;

	bool isDoAllFrame;

public:
	float			frameWidth;	// Width of frame 
	float			frameHeight;	// Height of frame
	float			frameTime;	// time giua 2 frame cua animation

	Animation();
	~Animation();

	bool Initialize(Sprite *sprite, float frameWidth, float frameHeight, float frameTime);

	void Update(float gameTime);

	// Nhap mot vector bao gom cac toa do theo hang va cot de dua no vao lAnimation
	void AddAnimation(int animId, std::vector<D3DXVECTOR2> animation);

	// Draw the frame with frame number, -1 return animation
	void Render(Sprite *sprite, bool isLeft, ViewPort *viewPort);

	void DoAnimation(int animId);

	bool CheckDoAllFrame() { return isDoAllFrame; }

	int GetCurrentFrame() { return currentFrame; }

	void SetDoAllFrame(bool status) { isDoAllFrame = status; }
};

#endif