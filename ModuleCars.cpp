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

	for (int i = 0; i < 8; ++i)
		crash.frames.push_back({ MTILE_SIZE * 9, MTILE_SIZE * i, MTILE_SIZE, MTILE_SIZE });
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

	//mask = App->masks->AddCollider(SDL_Rect{ position.x, position.y, 60, 90 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModuleCars::CleanUp()
{
	LOG("Unloading Cars");

	//App->masks->eraseCollider(mask->id);

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
	moving = new_state;
	if (moving == RIGHT){
		position.x += 4;
		if (position.x > (App->window->screen_surface->w - MTILE_SIZE))
			position.x = (App->window->screen_surface->w - MTILE_SIZE);
	}
	else{
		position.x -= 4;
		if (position.x < 0)
			position.x = 0;

		//mask->SetPos(position);
	}

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