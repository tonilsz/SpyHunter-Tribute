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
	bool OnCollision(Collider* a, Collider *b, COLISION_STATE status);
	void SetState(int new_state);
	//void SetMovement(Movement new_state);
	void UpGear();
	void DownGear();

	int pos;
	SDL_Rect turbo;

private:
};

#endif // __MODULEPLAYER_H__