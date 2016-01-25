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
	bool OnColision(Collider* a, Collider *b, COLISION_STATE status);
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

	int oil;
	int spray;
	int rocket;
	int truck;
	int lives;
	int pos;
	int score;
	int first_mode;
	int block_points;
	int rumble;
	int turbo_gear;
	int gear;
	SDL_Rect turbo;
	Timer state_timer;
	Weapon weapon = NONE;
	bool gun_turn;
	bool god_mode;

};

#endif // __MODULEPLAYER_H__