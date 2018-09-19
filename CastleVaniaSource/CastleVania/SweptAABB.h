#ifndef _SWEPT_AABB_H
#define _SWEPT_AABB_H
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#include <cmath>
#include <algorithm> 
#include <limits>
// describes an axis-aligned rectangle with a velocity
struct Box
{
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	Box(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = 0.0f;
		vy = 0.0f;
	}

	// toa do
	float x, y;

	// chieu dai, chieu rong
	float w, h;

	// van toc
	float vx, vy;
};

static bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

// returns true if the boxes are colliding (velocities are not used)
// moveX and moveY will return the movement the b1 must move to avoid the collision
static bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float left = b2.x - (b1.x + b1.w);
	float right = (b2.x + b2.w) - b1.x;
	float top = b2.y - (b1.y + b1.h);
	float bottom = (b2.y - b2.h) - b1.y;

	// check that there was a collision
	if (left > 0 || right < 0 || top > 0 || bottom < 0)
		return false;

	// find the offset of both sides
	moveX = abs(left) < right ? left : right;
	moveY = abs(top) < bottom ? top : bottom;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// tao 1 hcn dua trên vi tri ban dau và ke tiep, sau do lay hcn do xet xem co chong len voi hinh kia ko. neu co thi va cham, ko thì ko xet tiep.
static Box GetSweptBroadphaseBox(Box b, int dt)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx * dt;
	broadphasebox.y = b.vy < 0 ? b.y : b.y + b.vy *dt;
	broadphasebox.w = b.vx > 0 ? b.vx * dt + b.w : b.w - b.vx * dt;
	broadphasebox.h = b.vy > 0 ? b.vy * dt + b.h : b.h - b.vy * dt;

	return broadphasebox;
}

// performs collision detection on moving box b1 and static box b2
// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
// normalx and normaly return the normal of the collided surface (this can be used to do a response)
static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//tinh khoang cach can xay ra va cham xInvEntry va khoang cach de ra khoi va cham xInvExit
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy < 0.0f)
	{
		yInvEntry = b2.y - (b1.y - b1.h);
		yInvExit = (b2.y - b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - (b1.y - b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)

	//tinh time de bat dau va cham va time ket thuc va cham theo moi phuong :
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1.vx * dt);
		xExit = xInvExit / (b1.vx * dt);
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1.vy * dt);
		yExit = yInvExit / (b1.vy * dt);
	}

	// thoi gian va cham la thoi gian lon nhat cua 2 truc (2 truc phai cung tiep xuc thi moi va cham)

	float entryTime = max(xEntry, yEntry);
	// thoi gian ket thuc va cham la thoi gian cua 2 truc, (chi can 1 truc roi khoi va cham)
	float exitTime = min(xExit, yExit);

	// neu ko co va cham
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		// xac dinh huong cua phap tuyen khi va cham
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f) //cham vao be mat ben phai
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f; //cham vao be mat ben trai
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f) //cham vao be mat phia tren 
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f; //cham vao be mat phia duoi
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}


#endif