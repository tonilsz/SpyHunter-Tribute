#include "Globals.h"
#include "Application.h"
#include "ModuleCars.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleRoad.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleDriver.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

ModuleCars::ModuleCars(CARS car_type, int gear, bool start_enabled)
	: Module(start_enabled),
	gear(gear),
	dist(0),
	car_type(car_type)
{
	position.x = RTILE_WIDTH * 10;//RANDOM []
	position.y = RTILE_HEIGHT * 6.5;

	last_position = position;

	idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });
	idle.frames.push_back({ MTILE_SIZE * 1, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });
	idle.speed = 0.2f;

	right.x = MTILE_SIZE * 2;
	right.y = MTILE_SIZE * car_type;
	right.w = MTILE_SIZE;
	right.h = MTILE_SIZE;

	left.x = MTILE_SIZE * 3;
	left.y = MTILE_SIZE * car_type;
	left.w = MTILE_SIZE;
	left.h = MTILE_SIZE;

	for (int i = 3; i < 11; ++i)
		crash.frames.push_back({ MTILE_SIZE * i, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });
	crash.speed = 0.2f;


}

ModuleCars::~ModuleCars()
{
	// Homework : check for memory leaks
}

bool ModuleCars::Start()
{
	LOG("Loading Cars");
	return true;
}

// Load assets
// Load Colliders
bool ModuleCars::Resume()
{
	LOG("Init Cars");

	COLLIDER_TYPE colider = COL_CAR;
	int dif = 10;

	mask = App->masks->AddCollider(SDL_Rect{ position.x + dif, position.y, 44, 44 }, colider, this);


	/*
	enum CARS { PLAYER = 0, RED_CAR = 1, BLUE_CAR = 2, MOTO = 3, TRUCK = 4, ROAD_LORD = 6, SWITCH_BLADE = 7, ENFORCER = 8, MAD_BOMBER = 10 };
	enum COLLIDER_TYPE
	{
	COL_NONE = -1,
	COL_CAR,
	COL_PLAYER,
	COL_TRUCK,
	COL_ROAD_LORD,
	COL_MAD_BOMBER,
	COL_OIL,
	COL_SPRAY,
	COL_BULLET,
	COL_BULLET_ENEMY,
	COL_ROCKET,
	COL_BOMB,
	COL_ROAD_OUT,
	COL_ROAD_BORDER,
	COL_PUDDLE,
	COL_MAX
	};
	*/

	return true;
}

// Unload assets
bool ModuleCars::CleanUp()
{
	LOG("Unloading Cars");

	App->masks->colliders.remove(mask);

	return true;
}


update_status ModuleCars::PreUpdate()
{
	if (last_position.x == position.x)
		moving = STRAIGHT;
	else if (last_position.x < position.x)
		moving = RIGHT;
	else if (last_position.x > position.x)
		moving = LEFT;

	dist += (gear - App->player->gear);

	last_position = position;

	return UPDATE_CONTINUE;
}

void ModuleCars::SetState(int new_state){
	/*if (state != HADOUKEN && state != JUMP && state != WON){
	state = new_state;
	if (state == JUMP)
	jump_live.Start();
	if (state == HADOUKEN)
	hado_live.Start();
	if (state == WON)
	won_live.Start();
	}*/

}

void ModuleCars::SetMovement(Movement new_state){

	int dif = position.x - mask->rect.x;

	moving = new_state;
	if (moving == RIGHT){
		mask->rect.x += 4;
	}
	else if (moving == LEFT){
		mask->rect.x -= 4;
	}

	if (mask->rect.x < 0)
		mask->rect.x = 0;
	if (mask->rect.x >(App->window->screen_surface->w - MTILE_SIZE))
		mask->rect.x = (App->window->screen_surface->w - MTILE_SIZE);

	position.x = mask->rect.x + dif;
}

update_status ModuleCars::Update()
{
	switch (moving){
	case STRAIGHT:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_CAR, dist);
		break;
	case RIGHT:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &right, 1.0f, RENDER_CAR, dist);
		break;
	case LEFT:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &left, 1.0f, RENDER_CAR, dist);
		break;
	}
	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModuleCars::OnCollision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Player");
	return true;
}
void ModuleCars::UpGear(){
	if (gear != 8)
		gear += 4;
}

void ModuleCars::DownGear(){
	if (gear != 0)
		gear -= 4;
}