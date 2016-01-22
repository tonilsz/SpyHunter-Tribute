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
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled, CARS car)
	: ModuleCars(PLAYER, 0, start_enabled),
	pos(0),
	lives(1), 
	oil(0),
	spray(0),
	rocket(0),
	truck(0),
	gun_turn(false),
	god_mode(false)
{
	gear = 0;
	position.x = RTILE_WIDTH * 9;
	position.y = RTILE_HEIGHT * 6;

	last_position = position;

	turbo.x = MTILE_SIZE * 12;
	turbo.y = MTILE_SIZE * PLAYER;
	turbo.w = MTILE_SIZE;
	turbo.h = MTILE_SIZE;

	state_timer = Timer();
	first_mode = 0;

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

	score = 0;

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
	score += gear / 2;
	if (first_mode<1000)
		++first_mode;
	if (last_position.x == position.x)
		moving = STRAIGHT;
	else if (last_position.x < position.x)
		moving = RIGHT;
	else if (last_position.x > position.x)
		moving = LEFT;

	App->renderer->camera.y += gear;
	pos += (gear );
	if (pos > (RTILE_HEIGHT -1 )){
		pos = 0;
		App->renderer->camera.y = -1.5 * RTILE_HEIGHT;
		App->road->AddLine();
	}

	last_position = position;
	mask->rect.y = position.y - pos - gear;
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

void ModulePlayer::SetMovement(Movement new_state){

	moving = new_state;

	int dif = position.x - mask->rect.x;

	if (moving == RIGHT){
		mask->rect.x += gear;
		App->audio->PlayFx(AUD_TURN);
	}
	else if (moving == LEFT){
		mask->rect.x -= gear;
		App->audio->PlayFx(AUD_TURN);
	}
	if (mask->rect.x < 0)
		mask->rect.x = 0;

	if (mask->rect.x >(App->window->screen_surface->w - STILE_SIZE))
		mask->rect.x = (App->window->screen_surface->w - STILE_SIZE);

	position.x = mask->rect.x + dif;
}

void ModulePlayer::SetWeapon(Weapon new_weapon){
	if (weapon != WORKING || weapon == ROCKET || new_weapon == NONE){
		switch (new_weapon){
		case OIL:
			if (oil > 0){
				--oil;
				weapon = new_weapon;
			}
			break;
		case SPRAY:
			if (spray > 0){
				--spray;
				weapon = new_weapon;
			}
			break;
		case ROCKET:
			if (rocket > 0){
				--rocket;
				weapon = new_weapon;
			}
			break;
		case GUN:
		case NONE:
			weapon = new_weapon;
			break;
		}
	}
}

update_status ModulePlayer::Update()
{

	if ((score > 29999 && score < 30004) || (score > 59999 && score < 60004) || (score > 89999 && score < 90004) || (score > 119999 && score < 120004)){
		if (lives < 3)
			++lives;
		if (truck < 3)
			++truck;

	}

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

	if (lives == 0)
		App->road->SetGameState(G_OVER);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::OnColision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Player");
	/*
	if (a->type == COL_PLAYER && b->type == COL_ROAD_OUT){
		App->particles->addParticle(mask->rect.x, mask->rect.y + mask->rect.h, ANIM_EXPLOTE);
		if ((first_mode >= 1000))
			--App->player->lives;
		App->player->position.x = RTILE_WIDTH * 9;
		App->player->mask->rect.x = RTILE_WIDTH * 9 + 21;
		App->player->gear = 0;
	}
	if (a->type == COL_PLAYER && b->type == COL_BOMB){
		App->particles->addParticle(mask->rect.x, mask->rect.y + mask->rect.h, ANIM_EXPLOTE);
		gear = 0;
		if ((first_mode>=1000))
			--App->player->lives;
		App->player->position.x = RTILE_WIDTH * 9;
		App->player->mask->rect.x = RTILE_WIDTH * 9 + 21;
		App->player->gear = 0;
	}*/
	/*if (a->type == COL_PLAYER && b->type == COL_CAR){
		if (a->rect.x > b->rect.x)
			SetMovement(LEFT);
		else
			SetMovement(RIGHT);
	}*/

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

void ModulePlayer::GodMode(){
	if (god_mode){
		idle.frames.clear();
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });

		right.y = MTILE_SIZE * car_type;

		left.y = MTILE_SIZE * car_type;
		mask->SetEnabled(true);
	}
	else{
		idle.frames.clear();
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * 14.5, MTILE_SIZE, MTILE_SIZE });
		idle.frames.push_back({ MTILE_SIZE * 1, MTILE_SIZE * 14.5, MTILE_SIZE, MTILE_SIZE });

		right.y = MTILE_SIZE * 14.5;

		left.y = MTILE_SIZE * 14.5;
		mask->SetEnabled(false);
	}

	god_mode = !god_mode;
}


void ModulePlayer::GetRandWeapon(){
	int new_weapon = App->GetRand(3,1);
	switch (new_weapon){
	case 0:
		App->player->oil = 99;

	}
	switch (new_weapon){
	case 1:
		App->player->spray = 49;

	}
	switch (new_weapon){
	case 2:
		App->player->rocket = 9;

	}
	if (god_mode){
		idle.frames.clear();
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });

		right.y = MTILE_SIZE * car_type;

		left.y = MTILE_SIZE * car_type;
		mask->SetEnabled(true);
	}
	else{
		idle.frames.clear();
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * 14.5, MTILE_SIZE, MTILE_SIZE });
		idle.frames.push_back({ MTILE_SIZE * 1, MTILE_SIZE * 14.5, MTILE_SIZE, MTILE_SIZE });

		right.y = MTILE_SIZE * 14.5;

		left.y = MTILE_SIZE * 14.5;
		mask->SetEnabled(false);
	}

	god_mode = !god_mode;
}

