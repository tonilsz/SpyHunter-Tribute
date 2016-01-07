#ifndef __COLLIDER_H__
#define __COLLIDER_H__
#include "Module.h"
#include "Globals.h"
#include "Point.h"

enum COLLIDER_TYPE
{
	COL_NONE = -1,
	COL_CAR,
	COL_PLAYER,
	COL_TRUCK,
	COL_ROAD_LORD,
	COL_MAD_BOMBER,
	COL_OIL,
	COL_SPRAY,
	COL_BULLET,
	COL_BULLET_ENEMY,
	COL_ROCKET,
	COL_BOMB,
	COL_ROAD_OUT,
	COL_ROAD_BORDER,
	COL_PUDDLE,
	COL_MAX
};

enum COLISION_STATE
{
	COL_START,
	COL_DURING,
	COL_END
};

class Collider
{
public:
	SDL_Rect rect;
	bool to_delete;
	bool to_erase;
	COLLIDER_TYPE type;
	Module* callback;
	bool isCollising; 

	Collider::Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false),
		to_erase(false),
		isCollising(false)
	{}

	void Collider::SetPos(fPoint pos)
	{
		rect.x = pos.x;
		rect.y = pos.y;
	}

	bool Collider::CheckCollision(SDL_Rect r) const
	{
		return SDL_HasIntersection(&rect, &r);
	}
};

#endif // __COLLIDER_H__