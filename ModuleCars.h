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
enum Status { IDLE, TURBO, BREAK, TO_BORDER, EXPLOTE, DEAD};
enum Weapon { NONE = -1, GUN, OIL, SPRAY, ROCKET, BOMB, RAZOR, BULLET_ENEMY, WORKING };
enum CARS { PLAYER = 0, RED_CAR = 1, BLUE_CAR = 2, MOTO = 3, TRUCK = 4, ROAD_LORD = 6, SWITCH_BLADE = 7, ENFORCER = 8 , MAD_BOMBER = 10 };

class ModuleCars : public Module
{
public:
	ModuleCars(CARS car, bool start_enabled = true);
	~ModuleCars();

	virtual bool Start();
	virtual bool Resume();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual bool CleanUp();
	virtual bool OnColision(Collider* a, Collider *b, COLISION_STATE status);
	virtual void SetMovement(Movement new_state);
	virtual void SetState(Status new_state);
	virtual void UpVelocity();
	virtual void DownVelocity();
	fPoint GetPivot();
	virtual void SetWeapon(Weapon new_weapon);
	void TurnRandom();
	static int SetCarStartPosition(int velocity = 0, bool top = false);
	void AddCarPoints();

	Weapon weapon;
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
	float velocity;
	bool to_delete;

private:
};

#endif // __MODULECARS_H__