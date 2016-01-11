#ifndef __MODULECARS_H__
#define __MODULECARS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"
#include "ModuleCollision.h"


struct SDL_Texture;

enum Movement { STRAIGHT, RIGHT, LEFT };
enum Status { IDLE, TURBO, BREAK};
enum Weapon { NONE = -1, GUN, OIL, SPRAY, ROCKET };
enum CARS { PLAYER = 0, RED_CAR = 1, BLUE_CAR = 2, MOTO = 3, TRUCK = 4, ROAD_LORD = 6, SWITCH_BLADE = 7, ENFORCER = 8 , MAD_BOMBER = 10 };

class ModuleCars : public Module
{
public:
	ModuleCars(CARS car, int gear = 0, bool start_enabled = true);
	~ModuleCars();

	virtual bool Start();
	virtual bool Resume();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual bool CleanUp();
	virtual bool OnCollision(Collider* a, Collider *b, COLISION_STATE status);
	virtual void SetState(int new_state);
	virtual void SetMovement(Movement new_state);
	virtual void UpGear();
	virtual void DownGear();

	CARS car_type;
	int dist;
	Animation idle;
	SDL_Rect right;
	SDL_Rect left;
	Animation crash;
	fPoint position;
	fPoint last_position;
	Movement moving = STRAIGHT;
	Status state = IDLE;
	Timer clock;
	Collider* mask;
	int gear;

private:
};

#endif // __MODULECARS_H__