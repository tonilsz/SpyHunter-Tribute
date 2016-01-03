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
	pos(0)
{
	gear = 0;
	position.x = RTILE_WIDTH * 11.5;
	position.y = RTILE_HEIGHT * 6;

	last_position = position;

	turbo.x = MTILE_SIZE * 3;
	turbo.y = MTILE_SIZE * PLAYER;
	turbo.w = MTILE_SIZE;
	turbo.h = MTILE_SIZE;

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

	//mask = App->masks->AddCollider(SDL_Rect{ position.x, position.y, 60, 90 }, COLLIDER_PLAYER, this);

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

update_status ModulePlayer::Update()
{

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
	/*
	switch (state){
	case IDLE:
		switch (moving){
		case IDLE:
			break;
		case FOWARD:
			App->renderer->Blit(graphics, position.x, position.y, &(foward.GetCurrentFrame()), 0.75f);
			break;
		case BACKWARD:
			App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()), 0.75f);
			break;
		}
		break;
	case JUMP:
		if (jump_llive.running == true){
			if (jump_live.GetTime() < 100){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(0)), 0.75f);
			}
			else if (jump_live.GetTime() < 200){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(1)), 0.75f);
			}
			else if (jump_live.GetTime() < 300){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(2)), 0.75f);
			}
			else if (jump_live.GetTime() < 500){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(3)), 0.75f);
			}
			else if (jump_live.GetTime() < 600){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(4)), 0.75f);
			}
			else if (jump_live.GetTime() < 700){
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(5)), 0.75f);
			}
			else {
				App->renderer->Blit(graphics, position.x, position.y - 44, &(jump.GetFrame(6)), 0.75f);
			}

			if (jump_live.GetTime() > 800)
				jump_live.Stop();

		}
		else{
			state = IDLE;
		}

		break;
	case HADOUKEN:
		if (hado_live.running == true){
			if (hado_live.GetTime() < 100){
				App->renderer->Blit(graphics, position.x, position.y, &(hado.GetFrame(0)), 0.75f);
			}
			else if (hado_live.GetTime() < 200){
				App->renderer->Blit(graphics, position.x, position.y, &(hado.GetFrame(1)), 0.75f);
			}
			else if (hado_live.GetTime() < 300){
				App->renderer->Blit(graphics, position.x, position.y, &(hado.GetFrame(2)), 0.75f);
			}
			else {
				App->renderer->Blit(graphics, position.x, position.y, &(hado.GetFrame(3)), 0.75f);
			}

			if (hado_live.GetTime() > 500){
				hado_live.Stop();
				state = IDLE;
			}

		}
		else{
			state = IDLE;
		}
		break;
	case WON:
		if (won_live.running == true){
			if (won_live.GetTime() < 100){
				App->renderer->Blit(graphics, position.x, position.y-32, &(won.GetFrame(0)), 0.75f);
			}
			else if (won_live.GetTime() < 200){
				App->renderer->Blit(graphics, position.x, position.y - 32, &(won.GetFrame(1)), 0.75f);
			}
			else if (won_live.GetTime() < 300){
				App->renderer->Blit(graphics, position.x, position.y - 32, &(won.GetFrame(2)), 0.75f);
			}
			else {
				App->renderer->Blit(graphics, position.x, position.y - 32, &(won.GetFrame(3)), 0.75f);
			}

			if (won_live.GetTime() > 5000){
				won_live.Stop();
				state = IDLE;
			}

		}
		else{
			state = IDLE;
		}
		break;
	}

	
	*/
	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModulePlayer::OnCollision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Player");
	return true;
}
void ModulePlayer::UpGear(){
	if (gear < 8)
		gear += 4;
}

void ModulePlayer::DownGear(){
	if (gear > 0)
		gear -= 4;
}