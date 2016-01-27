#ifndef __MODULEDRIVER_H__
#define __MODULEDRIVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Timer.h"
#include "ModuleCollision.h"
#include "ModuleCars.h"

#define MAX_CARS 6

struct SDL_Texture;

class ModuleDriver : public Module
{
public:
	ModuleDriver(bool start_enabled = true);
	~ModuleDriver();

	bool Start();
	bool Resume();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool Stop();

	void AddCar(CARS car_type = RED_CAR);
	CARS GetRandomCar();

	//Contains the cars
	vector<ModuleCars*>* garage;

	//Number of bombs throwed by copter
	int seek_max;

	//Car Generation Handler
	int car_generation_handler;

	SDL_Texture* graphics = nullptr;
};

#endif // __MODULEDRIVER_H__