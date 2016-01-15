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
#include "ModuleAudio.h"
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

	App->audio->PlayFx(AUD_COPTER, -1);

}

ModuleCopter::~ModuleCopter()
{
	// Homework : check for memory leaks
}


update_status ModuleCopter::PreUpdate()
{
	dist += (App->player->GetPivot().y - 100) > GetPivot().y;

	if (App->player->gear != 0 && seeker < 5)
		Seek();
	else{
		SetMovement(N);
		gear = 9;
	}
	

	last_position = position;

	return UPDATE_CONTINUE;
}

void ModuleCopter::Seek(){

	if ((App->player->GetPivot().x) > GetPivot().x - 5 && (App->player->GetPivot().x ) < GetPivot().x + 5){
		if ((App->player->GetPivot().y) < GetPivot().y + 105 && (App->player->GetPivot().y) > GetPivot().y + 95){
			//IDLE
			if (App->player->gear > gear)
				++gear;

			if (App->player->gear < gear)
				--gear;

			ThrowBomb();
		}
		else if ((App->player->GetPivot().y - 106) < GetPivot().y - 10){
			SetMovement(N);

		}
		else if ((App->player->GetPivot().y - 94) > GetPivot().y + 10){
			SetMovement(S);
		}
	}
	else if ((App->player->GetPivot().x) < GetPivot().x){
		if ((App->player->GetPivot().y) < GetPivot().y + 105 && (App->player->GetPivot().y) > GetPivot().y + 95){
			//IDLE
			SetMovement(W);
		}
		else if ((App->player->GetPivot().y - 106) < GetPivot().y - 10){
			SetMovement(NW);

		}
		else if ((App->player->GetPivot().y - 94) > GetPivot().y + 10){
			SetMovement(SW);
		}
	}
	else if ((App->player->GetPivot().x) > GetPivot().x){
		if ((App->player->GetPivot().y) < GetPivot().y + 105 && (App->player->GetPivot().y) > GetPivot().y + 95){
			//IDLE
			SetMovement(E);
		}
		else if ((App->player->GetPivot().y - 106) < GetPivot().y - 10){
			SetMovement(NE);

		}
		else if ((App->player->GetPivot().y - 94) > GetPivot().y + 10){
			SetMovement(SE);
		}
	}

	if ((App->player->GetPivot().y - 106) < GetPivot().y - 250)
		++gear;
	if ((App->player->GetPivot().y - 106) > GetPivot().y + 150)
		if ( gear > 1)
			--gear;

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

	position.x = mask->rect.x + dif.x;
	position.y = mask->rect.y + dif.y;
}

update_status ModuleCopter::Update()
{

	fPoint dif(position.x - mask->rect.x, position.y - mask->rect.y);
	App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetFrame(orientation * 2)), 1.0f, RENDER_ROAD, dist);
	App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetFrame((orientation * 2) + 1)), 1.0f, RENDER_ROAD, dist);
	App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(helix.GetCurrentFrame()), 1.0f, RENDER_ROAD, dist);
	
	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModuleCopter::CleanUp(){
	App->audio->StopFx();

	return ModuleCars::CleanUp();
}

bool ModuleCopter::OnColision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Copter");
	return true;
}

void ModuleCopter::ThrowBomb()
{
	if (weapon != WORKING){
		App->particles->addParticleBackground(mask->rect.x + (mask->rect.w / 2), mask->rect.y + (mask->rect.h / 2), ANIM_BOMB);
		++seeker;
		weapon = WORKING;
	}
}
