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
	bool CleanUp();
	void AddCar(CARS car_type = RED_CAR, int gear = 0);
	void ClearWeapon();
	CARS GetRandomCar();

	vector<ModuleCars*>* garage;
	int num_cars;
	SDL_Texture* graphics = nullptr;
};

#endif // __MODULEDRIVER_H__