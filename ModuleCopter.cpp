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

ModuleCopter::ModuleCopter(CARS car_type, int velocity, bool start_enabled)
	: ModuleCars(car_type, start_enabled),
	seeker(0),
	bomb_lapsus(0)
{

		for (int i = 0; i < 8; ++i){
			idle.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10, LTILE_SIZE, LTILE_SIZE });
			idle.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10 + LTILE_SIZE, LTILE_SIZE, LTILE_SIZE });
		}
		idle.speed = 0.1f;

		helix.frames.push_back({ LTILE_SIZE * 4, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
		helix.frames.push_back({ LTILE_SIZE * 5, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
		helix.speed = 0.4f;

		for (int i = 0; i < 4; ++i)
			crash.frames.push_back({ LTILE_SIZE * i, MTILE_SIZE * 10 + (LTILE_SIZE * 2), LTILE_SIZE, LTILE_SIZE });
		crash.speed = 0.05f;

		mask = App->masks->AddCollider(SDL_Rect{ position.x + 31, position.y + 26, 32, 64 }, COL_MAD_BOMBER, this);

		App->audio->PlayFx(AUD_COPTER, -1);
	
}

ModuleCopter::~ModuleCopter()
{
	// Homework : check for memory leaks
}


update_status ModuleCopter::PreUpdate()
{
	//Weapon counter
	if (weapon == WORKING){
		++bomb_lapsus;
		if (bomb_lapsus == 150){
			bomb_lapsus = 0;
			weapon = NONE;
		}
	}

	//IA seek
	if (App->player->velocity != 0 && seeker < App->driver->seek_max){
		if (state != EXPLOTE )
			Seek();
	}else{
		SetMovement(N);
		velocity = 7;
	}

	last_position = position;

	return UPDATE_CONTINUE;
}

//IA Seek
void ModuleCopter::Seek(){

 		if ((App->player->GetPivot().x) > GetPivot().x - 8 && (App->player->GetPivot().x) < GetPivot().x + 8){
		if ((App->player->GetPivot().y) < GetPivot().y + 105 && (App->player->GetPivot().y) > GetPivot().y + 95){
			//IDLE
			--velocity;
			SetMovement(N);
			ThrowBomb();
		}
		else if ((App->player->GetPivot().y) < GetPivot().y + 105){
			SetMovement(N);

		}
		else if ((App->player->GetPivot().y) > GetPivot().y + 95){
			SetMovement(S);
		}
	}
	else if ((App->player->GetPivot().x) < GetPivot().x){
		if ((App->player->GetPivot().y) < GetPivot().y + 105 && (App->player->GetPivot().y) > GetPivot().y + 95){
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
		++velocity;
	if ((App->player->GetPivot().y - 106) > GetPivot().y + 150)
		if (velocity > 1)
			--velocity;

}

//Movement orientation
void ModuleCopter::SetMovement(ORIENTATION_TYPE new_dir){

	orientation = new_dir;

	fPoint dif(position.x - mask->rect.x, position.y - mask->rect.y);

	switch (orientation){
	case N:
		mask->rect.y -= velocity;
		break;
	case NE:
		mask->rect.y -= velocity;
		mask->rect.x += velocity;
		break;
	case E:
		mask->rect.x += velocity;
		break;
	case SE:
		mask->rect.x += velocity;
		mask->rect.y += velocity;
		break;
	case S:
		mask->rect.y += velocity;
		break;
	case SW:
		mask->rect.y += velocity;
		mask->rect.x -= velocity;
		break;
	case W:
		mask->rect.x -= velocity;
		break;
	case NW:
		mask->rect.x -= velocity;
		mask->rect.y -= velocity;
		break;
	}

	position.x = mask->rect.x + dif.x;
	position.y = mask->rect.y + dif.y;
}

update_status ModuleCopter::Update()
{

	fPoint dif(position.x - mask->rect.x, position.y - mask->rect.y);

	if (state == EXPLOTE){

		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetCurrentFrame()), 1.0f, RENDER_ROAD);
		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetCurrentFrame()), 1.0f, RENDER_ROAD);
		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(crash.GetCurrentFrame()), 1.0f, RENDER_ROAD);
		
		if (crash.current_frame == 0){
			velocity = 0;
			App->audio->StopFx();
			App->audio->PlayFx(AUD_EXPLOSION);
			App->player->score += 750;
		}
		
		if (crash.Finished()){
			to_delete = true;
		}
	}
	else{
		//Spin up
		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetFrame(orientation * 2)), 1.0f, RENDER_ROAD);
		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(idle.GetFrame((orientation * 2) + 1)), 1.0f, RENDER_ROAD);
		App->renderer->Blit(App->driver->graphics, mask->rect.x - 31, mask->rect.y - 26, &(helix.GetCurrentFrame()), 1.0f, RENDER_ROAD);
	}

	last_position = position;
	return UPDATE_CONTINUE;
}

bool ModuleCopter::Stop(){
	App->audio->StopFx();

	helix.frames.clear();

	return ModuleCars::Stop();
}

bool ModuleCopter::OnColision(Collider* a, Collider *b)
{
	LOG("Collision Copter");

	if (a->type == COL_MAD_BOMBER && b->type == COL_ROCKET){
		state = EXPLOTE;
	}
	return true;
}

void ModuleCopter::ThrowBomb()
{
	if (weapon != WORKING){
		App->particles_top->addParticleBackground(mask->rect.x, mask->rect.y + (mask->rect.h / 2), ANIM_BOMB);
		++seeker;
		weapon = WORKING;
	}
}
