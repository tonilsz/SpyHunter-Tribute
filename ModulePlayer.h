#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"
#include "ModuleCars.h"
#include "ModuleCollision.h"


struct SDL_Texture;

class ModulePlayer : public ModuleCars
{
public:
	ModulePlayer(bool start_enabled = true, CARS car = PLAYER);
	~ModulePlayer();

	bool Start();
	bool Resume();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	bool OnColision(Collider* a, Collider *bs);

	void SetState(int new_state);
	void SetMovement(Movement new_state);
	void SetWeapon(Weapon new_state);
	void UpGear();
	void DownGear();
	void UpTurboGear();
	void DownTurboGear();
	void GodMode();
	void GetRandWeapon();
	void Dead();
	void Alive();
	int GetStartPosition();

	//Weapon counters
	int oil;
	int spray;
	int rocket;

	// new weapon counter
	int truck;

	//lives counter
	int lives;

	//relative position for print in correct place
	int pos;

	//Score counter
	int score;

	//There are 2 modes: 1 with a time counter an infinite lives; 2 controle for lives
	int first_mode;

	//block ++score when a civilian killed
	int block_points;

	//Used when collisioning with road border
	int rumble;

	//short 1 or long 2
	int turbo_gear;

	//acceleration
	int gear;

	//turbo image
	SDL_Rect turbo;
	//Turbo animation duration
	Timer state_timer;

	//Weapon that is being used
	Weapon weapon = NONE;

	//Shot gun on left or right
	bool gun_turn;

	//invencibility mode
	bool god_mode;

};

#endif // __MODULEPLAYER_H__