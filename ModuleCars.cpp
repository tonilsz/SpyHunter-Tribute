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


	if (car_type != MAD_BOMBER){
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });
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
	else{
		idle.frames.push_back({ LTILE_SIZE * 0, MTILE_SIZE * 10 + (LTILE_SIZE * 0), LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * 0, MTILE_SIZE * 10 + (LTILE_SIZE * 1), LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * 0 + (LTILE_SIZE * 4), MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * 0, MTILE_SIZE * 10 + (LTILE_SIZE * 0), LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * 0, MTILE_SIZE * 10 + (LTILE_SIZE * 1), LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * 0 + (LTILE_SIZE * 5), MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
		idle.speed = 0.4f;

		right.x = LTILE_SIZE * 2;
		right.y = LTILE_SIZE * car_type;
		right.w = LTILE_SIZE;
		right.h = LTILE_SIZE;

		left.x = LTILE_SIZE * 3;
		left.y = LTILE_SIZE * car_type;
		left.w = LTILE_SIZE;
		left.h = LTILE_SIZE;

		for (int i = 0; i < 8; ++i)
			crash.frames.push_back({ LTILE_SIZE * 9, LTILE_SIZE * i, LTILE_SIZE, LTILE_SIZE });
		crash.speed = 0.2f;
	}

	switch (car_type){
	case RED_CAR:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 20, position.y, 25, 40 }, COL_CAR, this);
		break;
	case BLUE_CAR:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 20, position.y, 23, 32 }, COL_CAR, this);
		break;
	case MOTO:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 23, position.y, 19, 32 }, COL_CAR, this);
		break;
	case TRUCK:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 17, position.y, 32, 64 }, COL_TRUCK, this);
		break;
	case ROAD_LORD:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 18, position.y, 28, 41 }, COL_ROAD_LORD, this);
		break;
	case SWITCH_BLADE:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 19, position.y, 24, 41 }, COL_CAR, this);
		break;
	case ENFORCER:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 17, position.y, 28, 58 }, COL_CAR, this);
		break;
	case MAD_BOMBER:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 31, position.y + 26, 32, 64 }, COL_MAD_BOMBER, this);
		break;
	}


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
	mask->rect.y -= gear;

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

	int dif = position.x - mask->rect.x;

	if (moving == RIGHT)
		mask->rect.x += 4;
	else if (moving == LEFT)
		mask->rect.x -= 4;

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
		if (car_type != MAD_BOMBER){
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
		}
		else{
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
		}
		break;
	case RIGHT:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &right, 1.0f, RENDER_OTHER, dist);
		break;
	case LEFT:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &left, 1.0f, RENDER_OTHER, dist);
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