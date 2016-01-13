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
#include "ModuleCars.h""
#include "ModuleCopter.h"
#include "SDL/include/SDL.h"

ModuleCopter::ModuleCopter(CARS car_type, int gear, bool start_enabled)
	: ModuleCars(car_type, gear, start_enabled),
	seeker(0)
{

	for (int i = 0; i < 8; ++i){
		idle.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10 , LTILE_SIZE, LTILE_SIZE });
		idle.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10 + LTILE_SIZE, LTILE_SIZE, LTILE_SIZE });
	}
	idle.speed = 0.4f;

	helix.frames.push_back({ LTILE_SIZE * 4, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
	helix.frames.push_back({ LTILE_SIZE * 5, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
	helix.speed = 0.4f;

	for (int i = 0; i < 4; ++i)
		crash.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });

	crash.speed = 0.02f;
	
	mask = App->masks->AddCollider(SDL_Rect{ position.x + 31, position.y + 26, 32, 64 }, COL_MAD_BOMBER, this);

}

ModuleCopter::~ModuleCopter()
{
	// Homework : check for memory leaks
}


update_status ModuleCopter::PreUpdate()
{
	//SetMovement(N);
	++seeker;
	if (seeker > 1){
		seeker = 0;
		Seek();
	}

	return ModuleCars::PreUpdate();
}

void ModuleCopter::Seek(){

	if ((App->player->GetPivot().x) < GetPivot().x){
		if ((App->player->GetPivot().y - LTILE_SIZE) < GetPivot().y){
			SetMovement(NW);

		}
		else if ((App->player->GetPivot().y - LTILE_SIZE) < GetPivot().y){
			SetMovement(SW);

		}
		else{
			SetMovement(E);
		}
	}
	else if ((App->player->GetPivot().x) > GetPivot().x){
		if ((App->player->GetPivot().y - LTILE_SIZE) < GetPivot().y){
			SetMovement(NE);

		}
		else if ((App->player->GetPivot().y - LTILE_SIZE) < GetPivot().y){
			SetMovement(SE);

		}
		else{
			SetMovement(W);

		}
	}
	else{
		if ((App->player->GetPivot().y) < GetPivot().y){
			SetMovement(N);

		}
		else{
			SetMovement(S);

		}
	}
}

void ModuleCopter::SetMovement(ORIENTATION_TYPE new_dir){

	orientation = new_dir;

	fPoint dif(position.x - mask->rect.x, position.y - mask->rect.y);

	switch (orientation){
	case N:
		mask->rect.y -= gear;
		break;
	case NE:
		mask->rect.y -= gear;
		mask->rect.x += gear;
		break;
	case E:
		mask->rect.x += gear;
		break;
	case SE:
		mask->rect.x += gear;
		mask->rect.y += gear;
		break;
	case S:
		mask->rect.y += gear;
		break;
	case SW:
		mask->rect.y += gear;
		mask->rect.x -= gear;
		break;
	case W:
		mask->rect.x -= gear;
		break;
	case NW:
		mask->rect.x -= gear;
		mask->rect.y -= gear;
		break;
	}


	if (moving == RIGHT)
		mask->rect.x += 4;
	else if (moving == LEFT)
		mask->rect.x -= 4;

	if (mask->rect.x < 0)
		mask->rect.x = 0;

	if (mask->rect.x >(App->window->screen_surface->w - MTILE_SIZE))
		mask->rect.x = (App->window->screen_surface->w - MTILE_SIZE);

	position.x = mask->rect.x + dif.x;
	position.y = mask->rect.y + dif.y;
}

update_status ModuleCopter::Update()
{

	App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetFrame(orientation*2)), 1.0f, RENDER_OTHER, dist);
	App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(idle.GetFrame((orientation * 2)+1)), 1.0f, RENDER_OTHER, dist);
	App->renderer->Blit(App->driver->graphics, position.x, position.y - gear, &(helix.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModuleCopter::OnCollision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Copter");
	return true;
}
