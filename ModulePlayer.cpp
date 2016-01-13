#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleRoad.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleCars.h"
#include "ModuleDriver.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled, CARS car)
	: ModuleCars(PLAYER, 0, start_enabled),
	pos(0),
	gun_turn(false)
{
	gear = 0;
	position.x = RTILE_WIDTH * 11.5;
	position.y = RTILE_HEIGHT * 6;

	last_position = position;

	turbo.x = MTILE_SIZE * 12;
	turbo.y = MTILE_SIZE * PLAYER;
	turbo.w = MTILE_SIZE;
	turbo.h = MTILE_SIZE;

	state_timer = Timer();

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	return true;
}

// Load Colliders
bool ModulePlayer::Resume()
{
	LOG("Resume player");

	mask = App->masks->AddCollider(SDL_Rect{ position.x + 21, position.y, 24, 41 }, COL_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return ModuleCars::CleanUp();
}


update_status ModulePlayer::PreUpdate()
{
	if (last_position.x == position.x)
		moving = STRAIGHT;
	else if (last_position.x < position.x)
		moving = RIGHT;
	else if (last_position.x > position.x)
		moving = LEFT;

	App->renderer->camera.y += gear;
	pos += gear;
	if (pos > 63){
		pos = 0;
		App->renderer->camera.y = -1.5 * RTILE_HEIGHT;
		App->road->AddLine();
	}

	last_position = position;
	mask->rect.y = position.y - pos - ( gear);
	return UPDATE_CONTINUE;
}

void ModulePlayer::SetState(int new_state){
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
/*
void ModulePlayer::SetMovement(Movement new_state){
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

}*/

void ModulePlayer::SetWeapon(Weapon new_weapon){
	if (weapon != WORKING || weapon == ROCKET || new_weapon == NONE)
		weapon = new_weapon;
}

update_status ModulePlayer::Update()
{

	switch (state){
	case IDLE:
		switch (moving){
		case STRAIGHT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
			break;
		case RIGHT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &right, 1.0f, RENDER_PLAYER);
			break;
		case LEFT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &left, 1.0f, RENDER_PLAYER);
			break;
		}
		break;
	case TURBO:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &turbo, 1.0f, RENDER_PLAYER);
		if (state_timer.GetTime() > 100)
			state = IDLE;
		break;
	}

	switch (weapon){
	case GUN:
		if (gun_turn)
			App->particles->addParticle(position.x + 13, position.y - STILE_SIZE, ANIM_BULLET);
		else
			App->particles->addParticle(position.x + 21, position.y - STILE_SIZE, ANIM_BULLET);
		gun_turn = !gun_turn;
		weapon = WORKING;
		break;
	case OIL:
		App->particles->addParticle(position.x + 17, position.y + mask->rect.h, ANIM_OIL);
		weapon = WORKING;
		break;
	case SPRAY:
		App->particles->addParticle(position.x + 17, position.y + mask->rect.h, ANIM_SPRAY);
		weapon = WORKING;
		break;
	case ROCKET:
		App->particles->addParticle(position.x + 17, position.y - STILE_SIZE, ANIM_ROCKET);
		weapon = NONE;
		break;
	}

	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModulePlayer::OnCollision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Player");
	return true;
}
void ModulePlayer::UpGear(){
	if (gear < 8){
		gear += 4;
		state = TURBO;
		state_timer.Start();
	}
}

void ModulePlayer::DownGear(){
	if (gear > 0)
		gear -= 4;
}