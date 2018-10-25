#include "SweptAABBCollider.h"

std::vector<SweptAABBCollider*> SweptAABBCollider::listSweptAABB;

SweptAABBCollider::SweptAABBCollider() {};
SweptAABBCollider::~SweptAABBCollider() {};

Box SweptAABBCollider::GetSweptBoardpharseBox(Box box, float gameTime) {
	Box broadpharsebox;
	broadpharsebox.top = box.vy > 0 ? box.top + box.vy*gameTime : box.top;
	broadpharsebox.bottom = box.vy > 0 ? box.bottom : box.bottom + box.vy*gameTime;
	broadpharsebox.left = box.vx > 0 ? box.left : box.left + box.vx*gameTime;
	broadpharsebox.right = box.vx > 0 ? box.right + box.vx*gameTime : box.right;
	broadpharsebox.vx = box.vx;
	broadpharsebox.vy = box.vy;

	return broadpharsebox;
}

bool SweptAABBCollider::AABBCheck(Box b1, Box b2) {
	return !(b1.right < b2.left || b1.left > b2.right || b1.top < b2.bottom || b1.bottom > b2.top);
}

float SweptAABBCollider::SweptAABB(float gameTime, Box b1, Box b2, float &normalX, float &normalY) {
	//b2 move
	b1.vx = (b1.vx - b2.vx)* gameTime;
	b1.vy = (b1.vy - b2.vy)*gameTime;

	//khoang cach 2 box va cham/ thoat khoi va cham
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (b1.vx > 0) //box1 move tu trai qua
	{
		xInvEntry = b2.left - b1.right;
		xInvExit = b2.right - b1.left;
	}
	else {
		//box1 move tu phai qua
		xInvEntry = b2.right - b1.left;
		xInvExit = b2.left - b1.right;
	}

	if (b1.vy > 0.0f) //box1 di tu duoi len
	{
		yInvEntry = b2.bottom - b1.top; //truc theo the gioi thuc.truc Y huong len.
		yInvExit = b2.top - b1.bottom;
	}
	else {
		//box1 di tu tren xuong
		yInvEntry = b2.top - b1.bottom;
		yInvExit = b2.bottom - b1.top;
	}

	//thoi gian de va cham theo 2 truc
	float xEntry, xExit;
	float yEntry, yExit;

	if (b1.vx == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	//thoi gian lon nhat va nho nhat(ket thuc) va cham
	float entryTime = std::max(xEntry, xEntry);
	float exitTime = std::min(xExit, yExit);

	//truong hop ko xay ra va cham
	if (entryTime > exitTime || (xEntry<0.0f && yEntry<0.0f) || xEntry>1.0f || yEntry>1.0f) {
		normalX = 0.0f;
		normalY = 0.0f;
		return 1.0f;
	}

	//truong hop xay ra va cham, uoc tinh vector phap tuyen
	if (xEntry > yEntry) {
		//dung ve ben phai
		if (xInvEntry < 0.0f) {
			normalX = 1.0f;
			normalY = 0.0f;
		}
		//ve ben trai
		else {
			normalX = -1.0f;
			normalY = 0.0f;
		}
	}
	else {
		//dung o tren
		if (yInvEntry < 0.0f) {
			normalX = 0.0f;
			normalY = 1.0f;
		}
		//dung o duoi
		else {
			normalX = 0.0f;
			normalY = -1.0f;
		}
	}
	return entryTime; //time xay ra va cham
}

Box SweptAABBCollider::GetBox() { return box; };

void SweptAABBCollider::SetBox(Box _box) {
	box = _box;
}

int SweptAABBCollider::GetTag() { return tag; };
void SweptAABBCollider::SetTag(int _tag) { tag = _tag; };