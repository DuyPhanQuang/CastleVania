#ifndef _SWEPT_AABB_H
#define _SWEPT_AABB_H

#include "Global.h"
#include <math.h>
#include <algorithm>
#include <limits>

extern bool AABBCheck(Box object, Box other);
extern bool AABB(Box object, Box other, float& moveX, float& moveY);
extern Box GetSweptBroadphaseBox(Box obj);
extern int Collide(Box &box, Box &block, float& collisionTime, float& x, float& y);
extern float SweptAABB(Box object, Box other, float& normalX, float& normalY);
#endif
