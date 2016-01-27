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

ModuleDriver::ModuleDriver(bool start_enabled) : 
Module(start_enabled), 
car_generation_handler(300),
seek_max(3)
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

bool ModuleDriver::Resume()
{
	LOG("Init Cars");

	graphics = App->textures->Load("cars.png");

	for(int i = 0; i < 6; ++i){
		AddCar(GetRandomCar());
	}

	return true;
}

// Unload assets
bool ModuleDriver::Stop()
{
	bool ret = true;
	LOG("Unloading Cars");

	App->textures->Unload(graphics);

	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end(); ++it)
		ret = ret || (*it)->Stop();

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
			if ((*it)->state == DEAD)
				App->player->SetWeapon(NONE);
			if ( (*it)->car_type == MAD_BOMBER)
				App->audio->StopFx();
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

	// schedule colliders for deletion
	for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && ret == UPDATE_CONTINUE; ++it){
		if ((*it)->mask->rect.y > SCREEN_HEIGHT + 200 || (*it)->mask->rect.y < -200){
			(*it)->state = DEAD;
			(*it)->to_delete = true;
			//if the animation hasn't end we have to restore the Player Weapon
			App->player->SetWeapon(NONE);
		}
	}

	//Add new car?
	if (App->GetTicks() % car_generation_handler == 0)
		insert = true;

	//if car counter < max
	if (insert && App->driver->garage->size() < 6){
		AddCar(GetRandomCar());
	}

	return ret;
}

//Add new car
void ModuleDriver::AddCar(CARS car_type){
	//if copter, use especific constructor
	if (car_type == MAD_BOMBER)
		garage->push_back(new ModuleCopter(car_type, true));
	else
		garage->push_back(new ModuleCars(car_type, true));
}

//Generate a random car
CARS ModuleDriver::GetRandomCar(){
	bool find = false;
	unsigned int res = MOTO;

	res = App->GetRand(8,1);


	//Skip explosion anim
	if (res == 7)
		++++++res;
	//Skip truck and empty row
	if (res == 4 || res == 5)
		++++res;

	//do not have more than 1 copter in screen
	if (res == 10)
		for (vector<ModuleCars*>::iterator it = garage->begin(); it != garage->end() && !find; ++it)
			find = ((*it)->car_type == MAD_BOMBER);

	//if there is a copter, change it for a civilian
	if (find)
		res = App->GetRand(3, 1);

	return (CARS)res;
}