#ifndef __COLLIDER_H__
#define __COLLIDER_H__
#include "Module.h"
#include "Globals.h"
#include "Point.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE,
	COLLIDER_PLAYER,
	COLLIDER_CAR,
	COLLIDER_MAX
};

enum COLISION_STATE
{
	COLISION_START,
	COLISION_DURING,
	COLISION_END
};

struct Collider
{
	int id;
	SDL_Rect rect;
	bool enabled;
	COLLIDER_TYPE type;
	Module* callback;
	bool isCollising;

	Collider(){}

	Collider(int id, SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		id(id),
		rect(rectangle),
		type(type),
		callback(callback),
		enabled(true),
		isCollising(false)
	{}

	void SetPos(fPoint pos)
	{
		rect.x = pos.x;
		rect.y = pos.y;
	}

	bool CheckCollision(SDL_Rect r) const;
};

#endif // __COLLIDER_H__