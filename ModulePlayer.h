#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"
#include "ModuleCollision.h"


struct SDL_Texture;

enum state {IDLE, BACKWARD, FOWARD, HADOUKEN, JUMP, WON};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	bool OnCollision(Collider* a, Collider *b, COLISION_STATE status);
	void SetState(int new_state);
	void SetMovement(int new_state);

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation foward;
	Animation jump;
	Animation hado;
	Animation won;
	fPoint position;
	fPoint last_position;
	int moving = IDLE;
	int state = IDLE;
	Timer jump_live;
	Timer hado_live;
	Timer won_live;
	Collider* mask;
};

#endif // __MODULEPLAYER_H__