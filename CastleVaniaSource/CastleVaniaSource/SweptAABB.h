#ifndef _SWEPT_AABB_H
#define _SWEPT_AABB_H

#include "Global.h"

extern bool isColliding(Box object, Box other);
extern bool isAABB(Box object, Box other, float& moveX, float& moveY);
extern Box getSweptBroadphaseBox(Box obj);
extern int Collide(Box &object, Box &other, float& collisionTime, float& x, float& y);
extern float SweptAABB(Box object, Box other, float& normalX, float& normalY);

#endif
