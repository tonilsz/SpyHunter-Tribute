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
#include "ModulePlayer.h"
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

	GetRandomCar();

	AddCar(GetRandomCar(), rand() % 3 + 4);
	AddCar(GetRandomCar(), rand() % 3 + 4);
	AddCar(GetRandomCar(), rand() % 3 + 4);
	AddCar(GetRandomCar(), rand() % 3 + 4);
	AddCar(GetRandomCar(), rand() % 3 + 4);

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

	// Remove all colliders scheduled for deletion
	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE;)
	{
		(*it)->PreUpdate();
		if ((*it)->to_delete == true)
		{
			App->masks->colliders.remove((*it)->mask);
			RELEASE(*it);
			it = garage->erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
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

	bool insert = false;

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE; ++it){
		if ((*it)->mask->rect.y > SCREEN_HEIGHT + 200)
			(*it)->to_delete = true;
		if ((*it)->mask->rect.y < -200)
			(*it)->to_delete = true;
	}


	if (App->player->gear == 4){
		if (App->player->score % 3000 == 0 || App->player->score % 3001 == 0 || App->player->score % 3002 == 0 || App->player->score % 3003 == 0)
			insert = true;
	}
	else
		if (App->player->score % 3000 == 0 || App->player->score % 3001 == 0 || App->player->score % 3002 == 0 || App->player->score % 3003 == 0 ||
			App->player->score % 3004 == 0 || App->player->score % 3005 == 0 || App->player->score % 3006 == 0 || App->player->score % 3007 == 0)
			insert = true;

	if (insert && App->driver->garage->size() < 6){
		AddCar(GetRandomCar(), rand() % 3 + 4);
	}

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

CARS ModuleDriver::GetRandomCar(){
	bool find = false;
	unsigned int res = MOTO;

	srand(SDL_GetTicks() % (rand() % 50 + 1) + 1);

	res = rand() % 7 + 1;

	if (res == 7)
		++++++res;
	if (res == 4 || res == 5)
		++++res;

	if (res == 10)
		for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && !find; ++it)
			find = ((*it)->car_type == MAD_BOMBER);

	if (find)
		res = 1;

	return (CARS)res;
}