#include "Globals.h"
#include "Application.h"
#include "ModuleDriver.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleRoad.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleCars.h"
#include "ModuleCopter.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

ModuleDriver::ModuleDriver(bool start_enabled) : Module(start_enabled)
{
	garage = new vector<ModuleCars*>;
}

ModuleDriver::~ModuleDriver()
{
	// Homework : check for memory leaks
}

bool ModuleDriver::Start()
{
	LOG("Loading Cars");
	return true;
}

// Load assets
// Load Colliders
bool ModuleDriver::Resume()
{
	LOG("Init Cars");

	graphics = App->textures->Load("cars.png"); // arcade version

	AddCar(MOTO, rand() % 3 + 5);
	AddCar(RED_CAR, rand() % 3 + 5);
	AddCar(BLUE_CAR, rand() % 3 + 5);
	AddCar(TRUCK, rand() % 3 + 5);
	AddCar(ROAD_LORD, rand() % 3 + 5);
	AddCar(SWITCH_BLADE, rand() % 3 + 5);
	AddCar(ENFORCER, rand() % 3 + 5);
	AddCar(MAD_BOMBER, rand() % 3 + 5);

	return true;
}

// Unload assets
bool ModuleDriver::CleanUp()
{ 
	bool ret = true;
	LOG("Unloading Cars");

	App->textures->Unload(graphics);

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end(); ++it)
		ret = ret || (*it)->CleanUp();

	return ret;
}


update_status ModuleDriver::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	return ret;
}


update_status ModuleDriver::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	return ret;
}


update_status ModuleDriver::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

void ModuleDriver::AddCar(CARS car_type, int gear){
	if (car_type == MAD_BOMBER){
		garage->push_back(new ModuleCopter(car_type, gear, true));
		App->audio->PlayFx(AUD_COPTER, -1);
	}
	else
		garage->push_back(new ModuleCars(car_type, gear, true));
}

void ModuleDriver::ClearWeapon(){
	bool finded = false;

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && !finded; ++it){
		if ((*it)->car_type == MAD_BOMBER){
			finded = true;
			(*it)->SetWeapon(NONE);
		}

	}
}