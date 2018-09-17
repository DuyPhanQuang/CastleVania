#include <cmath>
#include "SweptAABB.h"
#include <math.h>
#include <algorithm>
#include <limits>

//kiem tra hai Box co va cham voi nhau hay khong. return true -> co va cham
bool isColliding(Box object, Box other) {
	float left = other.x - (object.x + object.w);
	float right = (other.x + other.w) - object.x;
	float top = (object.y + object.h) - other.y;
	float bottom = object.y - (other.y + other.h);

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

//moveX or moveY can di chuyen de tranh va cham
bool isAABB(Box object, Box other, float& moveX, float& moveY) {
	moveX = moveY = 0;
	float left = other.x - (object.x + object.w);
	float right = (other.x + other.w) - object.x;
	float top = (object.y + object.h) - other.y;
	float bottom = object.y - (other.y + other.h);

	if (left > 0 || right < 0 || top < 0 || bottom > 0) return false;
	moveX = abs(left) < right ? left : right;
	moveY = abs(bottom) < top ? bottom : top;

		//dung gia tri chenh lech nho nhat
		if (abs(moveX) < abs(moveY))
			moveY = 0;
		else
			moveX = 0;
		return true;
}

//xet va cham voi sweptAABB
float SweptAABB(Box object, Box other, float& normalX, float& normalY) {
	float dxEntry, dyEntry;
	float dxExit, dyExit;
	// khoang cach can de xay ra va cham dxEntry, dyEntry va khoang cach de ra khoi va cham dxExit, dyExit
	if (object.vx > 0) {
		dxEntry = other.x - (object.x + object.w);
		dxExit = (other.x + other.w) - object.x;
	}
	else {
		dxEntry = (other.x + other.w) - object.x;
		dxExit = other.x - (object.x + object.w);
	}
	if (object.vy > 0) {
		dyEntry = other.y - (object.y + object.h);
		dyExit = (other.y + other.h) - object.y;
	}
	else {
		dyEntry = (other.y + other.h) - object.y;
		dyExit = other.y - (object.y + object.h);
	}

	//thoi gian va cham va thoi gian ket thuc va cham theo phuong
	float txEntry, tyEntry;
	float txExit, tyExit;
	if (object.vx == 0) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else {
		txEntry = dxEntry / object.vx;
		txExit = dxExit / object.vx;
	}

	if (object.vy == 0) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else {
		tyEntry = dxEntry / object.vy;
		tyExit = dxExit / object.vy;
	}

	//thoi gian de box bat dau va cham va TG ket thuc va cham
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	//neu ko co va cham
	if (entryTime > exitTime || txEntry < 0 && tyEntry < 0 || txEntry > 1 || tyEntry > 1) {
		normalX = 0;
		normalY = 0;
		return 1;
	}
	else {
		//tinh toan binh thuong cua be mat va cham
		if (txEntry > tyEntry) {
			if (dxEntry < 0) {
				normalX = 1;
				normalY = 0;
			}
			else {
				normalX = -1;
				normalY = 0;
			}
		}
		else {
			if (dxEntry < 0) {
				normalX = 0;
				normalY = 1;
			}
			else {
				normalX = 0;
				normalY = -1;
			}
		}

		return entryTime; //thoi gian cua va cham
	}
}

Box getSweptBroadphaseBox(Box object) {
	float x = object.vx > 0 ? object.x : object.x + object.vx;
	float y = object.vy > 0 ? object.y : object.y + object.vy;
	float w = object.w + abs(object.vx);
	float h = object.h + abs(object.vy);
	return Box(x, y, w, h, 0, 0);
}

int Collide(Box &object, Box &other, float &collisionTime, float &x, float &y) {
	if (isColliding(getSweptBroadphaseBox(object), other)) {
		float normalX, normalY;
			collisionTime = SweptAABB(object, other, normalX,normalY);
			if (collisionTime < 1) {
				x = normalX;
				y = normalY;
				if (normalX == 1)
					return 1;
				if (normalX == -1)
					return 2;
				if (normalY == 1)
					return 3;
				if (normalY == -1)
					return 4;
			}
			else if (isColliding(object, other))
				return 5;
	}
}