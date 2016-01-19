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
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

ModuleCars::ModuleCars(CARS car_type, int gear, bool start_enabled)
	: Module(start_enabled),
	gear(gear),
	dist(0),
	car_type(car_type),
	weapon(NONE),
	to_delete(false)
{


	position.x = RTILE_WIDTH * 7;
	position.y = RTILE_HEIGHT * 6.5;

	if (car_type != PLAYER){

		if (App->player->gear < 5){
			position.y = RTILE_HEIGHT * 9;
		}
		else{
			position.y = RTILE_HEIGHT * 0;
		}

		position.x = SetLeftRight(); 
		position.y -= App->player->pos;
	}

	last_position = position;


	if (car_type != MAD_BOMBER){
		idle.frames.push_back({ MTILE_SIZE * 0, MTILE_SIZE * car_type, MTILE_SIZE, MTILE_SIZE });
		idle.speed = 20.0f;

		right.x = MTILE_SIZE * 2;
		right.y = MTILE_SIZE * car_type;
		right.w = MTILE_SIZE;
		right.h = MTILE_SIZE;

		left.x = MTILE_SIZE * 3;
		left.y = MTILE_SIZE * car_type;
		left.w = MTILE_SIZE;
		left.h = MTILE_SIZE;

		for (int i = 0; i < 12; ++i)
			crash.frames.push_back({ MTILE_SIZE * i, MTILE_SIZE * 9, MTILE_SIZE, MTILE_SIZE });
	}
	crash.speed = 0.1f;

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
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 17, position.y, 32, 64 }, COL_CAR, this);
		//mask = App->masks->AddCollider(SDL_Rect{ position.x + 17, position.y, 32, 64 }, COL_TRUCK, this);
		break;
	case ROAD_LORD:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 18, position.y, 28, 41 }, COL_CAR, this);
		//mask = App->masks->AddCollider(SDL_Rect{ position.x + 18, position.y, 28, 41 }, COL_ROAD_LORD, this);
		break;
	case SWITCH_BLADE:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 19, position.y, 24, 41 }, COL_CAR, this);
		break;
	case ENFORCER:
		mask = App->masks->AddCollider(SDL_Rect{ position.x + 17, position.y, 28, 58 }, COL_CAR, this);
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

	delete(mask);
	App->masks->colliders.remove(mask);

	return true;
}


update_status ModuleCars::PreUpdate()
{
	dist = 0;

	if (state == TO_BORDER){
		if (mask->rect.x > SCREEN_WIDTH / 2)
			SetMovement(LEFT);
		else
			SetMovement(RIGHT);
	}
	if (last_position.x == position.x)
		moving = STRAIGHT;
	else if (last_position.x < position.x)
		moving = RIGHT;
	else if (last_position.x > position.x)
		moving = LEFT;

	if (App->GetTicks() % 200 == 0 && mask->collisions.size() == 0 )
		TurnRandom();
	else
		moving = STRAIGHT;

	mask->rect.y -= gear;
	position.y = mask->rect.y + App->player->pos;

	last_position = position;

	return UPDATE_CONTINUE;
}

update_status ModuleCars::Update()
{
	if (state == EXPLOTE){
		if (crash.current_frame < 8)
			App->renderer->Blit(App->driver->graphics, position.x, position.y, &(idle.GetFrame(0)), 1.0f, RENDER_OTHER, dist);
		App->renderer->Blit(App->driver->graphics, position.x, position.y, &(crash.GetCurrentFrame()), 1.0f, RENDER_OTHER, dist);
		if (crash.current_frame > 8 && crash.current_frame < 9){
			gear = 0;
			App->audio->PlayFx(AUD_EXPLOSION);
		}
		if (crash.Finished()){
			state = DEAD;
			to_delete = true;
		}
	}
	else
	{
		switch (moving){
		case STRAIGHT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y, &(idle.GetFrame(0)), 1.0f, RENDER_OTHER, dist);
			break;
		case RIGHT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y, &right, 1.0f, RENDER_OTHER, dist);
			break;
		case LEFT:
			App->renderer->Blit(App->driver->graphics, position.x, position.y, &left, 1.0f, RENDER_OTHER, dist);
			break;
	}
}
	last_position = position;
	return UPDATE_CONTINUE;
}

void ModuleCars::SetMovement(Movement new_state){
	moving = new_state;

	int dif = position.x - mask->rect.x;

	if (moving == LEFT)
		mask->rect.x += gear * 2;
	else if (moving == RIGHT)
		mask->rect.x -= gear * 2;

	if (mask->rect.x < 0)
		mask->rect.x = 0;

	if (mask->rect.x >(App->window->screen_surface->w - mask->rect.w - 2))
		mask->rect.x = (App->window->screen_surface->w - mask->rect.w);

	position.x = mask->rect.x + dif;
}

void ModuleCars::SetState(Status new_state){
	if (state != TO_BORDER ){
		state = new_state;
	}

}
bool ModuleCars::OnColision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Car");

	if (b->type == COL_CAR || b->type == COL_PLAYER){
		if (a->rect.x > b->rect.x)
			SetMovement(LEFT);
		else if (a->rect.x < b->rect.x)
			SetMovement(RIGHT);
		else{
			if (App->GetRand(2) == 0)
				SetMovement(LEFT);
			else
				SetMovement(RIGHT);
		}

	}

	//if (a->type == COL_CAR && b->type == COL_ROAD_BORDER && !a->HasCollision()){
	if (b->type == COL_ROAD_BORDER ){
		if (state != TO_BORDER)
			if (a->rect.x >= b->rect.x)
				SetMovement(LEFT);
			else
				SetMovement(RIGHT);
	}

	if (status == COL_START){
		if (b->type == COL_ROAD_OUT){
			App->particles->addParticle(mask->rect.x, mask->rect.y + mask->rect.h, ANIM_EXPLOTE);
			state = DEAD;
			to_delete = true;
			gear = 0;
		}
		if (b->type == COL_SPRAY){
			state = TO_BORDER;
		}
		if (b->type == COL_OIL){
			state = TO_BORDER;
		}
		if (b->type == COL_BULLET){
			state = EXPLOTE;
		}
		if (b->type == COL_BOMB){
			state = EXPLOTE;
		}
	}

	if (status == COL_DURING){
		/*if (a->type == COL_CAR && b->type == COL_PLAYER){
			if (a->rect.x > b->rect.x)
				SetMovement(LEFT);
			else
				SetMovement(RIGHT);
		}*/
	}
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

fPoint ModuleCars::GetPivot(){
	fPoint res;
	res.x = mask->rect.x + mask->rect.w / 2;
	res.y = mask->rect.y;
	return res;
}

void ModuleCars::SetWeapon(Weapon new_weapon){
	if (weapon != WORKING || new_weapon == NONE)
		weapon = new_weapon;
}

void ModuleCars::TurnRandom(){
	int random = App->GetRand(10);
	if (random < 5)
		SetMovement(RIGHT);
	else
		SetMovement(LEFT);
}

int ModuleCars::SetCarStartPosition(bool top){

	int left = SCREEN_WIDTH;
	int right = 0;

	RoadLine * startLine = App->road->screen.back();
	if (App->player->gear < 5){
		startLine = *App->road->screen.begin();
	}

	for (vector<Collider*>::iterator it = startLine->mask->begin(); it != startLine->mask->end();){
		if ((*it)->type == COL_ROAD_BORDER){
			if ((*it)->rect.x < left)
				left = (*it)->rect.x;
			if ((*it)->rect.x > right)
				right = (*it)->rect.x;
		}
		++it;
	}

	left += RTILE_WIDTH * 1;
	right -= RTILE_WIDTH;

	if (left == right)
		right += RTILE_WIDTH;

	if (App->road->GetCurrentSegmentType() == S_2_BR || App->road->GetCurrentSegmentType() == S_2_ROADS)
		if (App->GetRand(2)){
			left = 2 * RTILE_WIDTH;
			right = 4 * RTILE_WIDTH;
		}
		else{
			left = 10 * RTILE_WIDTH;
			right = 12 * RTILE_WIDTH;
		}

	return App->GetRand((right - left), left);
}