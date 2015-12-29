#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect background_ship;
	SDL_Rect mooring_f;
	SDL_Rect mooring_b;
	Animation flag;
	Animation girl;
	Animation boat;
	Animation pair;
	Animation green;
	Animation blue;
	Animation brown;
	Animation pink;
};

#endif // __MODULESCENEKEN_H__