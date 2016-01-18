#ifndef __COLLIDER_H__
#define __COLLIDER_H__
#include "Module.h"
#include "Globals.h"
#include "Point.h"

enum COLLIDER_TYPE
{
	COL_NONE = -1,
	COL_CAR = 0,
	COL_PLAYER = 1,
	COL_TRUCK = 2,
	COL_ROAD_LORD = 3,
	COL_MAD_BOMBER = 4,
	COL_OIL = 5,
	COL_SPRAY = 6,
	COL_BULLET = 7,
	COL_BULLET_ENEMY = 8,
	COL_ROCKET = 9,
	COL_BOMB = 10,
	COL_ROAD_OUT = 11,
	COL_ROAD_BORDER = 12,
	COL_PUDDLE = 13,
	COL_MAX = 14
};

enum COLISION_STATE
{
	COL_START,
	COL_DURING,
	COL_END
};

using namespace std;
#include<list>

class Collider
{
public:
	SDL_Rect rect;
	bool to_delete;
	bool to_erase;
	COLLIDER_TYPE type;
	Module* callback;
	bool enabled;
	list<Collider *> collisions;

	Collider::Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false),
		to_erase(false)
	{}

	void Collider::SetPos(fPoint pos)
	{
		rect.x = pos.x;
		rect.y = pos.y;
	}

	void Collider::SetEnabled(bool enable)
	{
		enabled = enable;
	}

	bool Collider::CheckCollision(SDL_Rect r) const
	{
		return SDL_HasIntersection(&rect, &r);
	}

	bool IsCollising(Collider * crash){
		bool res = false;

		for (list<Collider *>::iterator it = collisions.begin(); it != collisions.end(); ++it)
			if (*it == crash)
				res = true;

		return res;
	}

	bool HasCollision(){
		return (bool)collisions.size();
	}

	void AddCollision(Collider * crash){
		collisions.push_back(crash);
	}

	void RemoveCollision(Collider * crash){
		collisions.remove(crash);
	}


};

#endif // __COLLIDER_H__