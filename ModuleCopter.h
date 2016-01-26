#ifndef __MODULECOPTER_H__
#define __MODULECOPTER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"
#include "ModuleCollision.h"
#include "ModuleCars.h"

enum ORIENTATION_TYPE {
	N, NE, E, SE, S, SW, W, NW
};

class ModuleCopter : public ModuleCars
{
public:
	ModuleCopter(CARS car, int velocity = 0, bool start_enabled = true);
	~ModuleCopter();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	bool OnColision(Collider* a, Collider *b);
	void SetMovement(ORIENTATION_TYPE new_dir);
	void Seek();
	void ThrowBomb();

	//Bomb throw lapsus
	int bomb_lapsus;
	
	//Number of Bombs Trhowed
	int seeker;

	//is seakeng the player?
	bool seeking;
	
	Animation helix;
	ORIENTATION_TYPE orientation;

};

#endif // __MODULECOPTER_H__