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
	: ModuleCars(PLAYER, start_enabled),
	pos(0),
	lives(1), 
	oil(0),
	spray(0),
	rocket(0),
	truck(0),
	block_points(0),
	rumble(0),
	gear(0),
	turbo_gear(1),
	gun_turn(false),
	god_mode(false)
{
	velocity = 0;
	position.x = RTILE_WIDTH * 11;
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

	mask = App->masks->AddCollider(SDL_Rect{ (int)position.x + 21, (int)position.y, 24, 41 }, COL_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::Stop()
{
	LOG("Unloading player");

	return ModuleCars::Stop();
}


update_status ModulePlayer::PreUpdate()
{
	//if a civilian is killed
	if (!block_points){
		score += velocity / 2;
	}
	else{
		++block_points;
		if (block_points == 100)
			block_points = 0;
	}

	//if we are in first mode
	if (first_mode<1000)
		++first_mode;

	//is moving to side?
	if (last_position.x == position.x)
		moving = STRAIGHT;
	else if (last_position.x < position.x)
		moving = RIGHT;
	else if (last_position.x > position.x)
		moving = LEFT;

	//reallocate camera
	App->renderer->camera.y += velocity;
	pos += velocity;
	if (pos > (RTILE_HEIGHT * SCREEN_SIZE)-1){
		pos -= ((RTILE_HEIGHT * SCREEN_SIZE));
		App->renderer->camera.y = -1.5 * RTILE_HEIGHT * SCREEN_SIZE + velocity;
		App->road->AddLine();
	}


	last_position = position;

	//reallocate mask
	mask->rect.y = position.y - ((pos / SCREEN_SIZE)) - velocity;

	rumble = 0;

	return UPDATE_CONTINUE;
}

void ModulePlayer::SetMovement(Movement new_state){

	moving = new_state;

	//get relative dist
	int dif = position.x - mask->rect.x;

	//turn side
	int movement = 2;
	if (gear != 0){
		if (moving == RIGHT){
			mask->rect.x += movement;
		}
		else if (moving == LEFT){
			mask->rect.x -= movement;
		}
	}

	//Control don't go out of the screen
	if (mask->rect.x < 0)
		mask->rect.x = 0;

	if (mask->rect.x >(App->window->screen_surface->w - STILE_SIZE))
		mask->rect.x = (App->window->screen_surface->w - STILE_SIZE);

	//set relative dist
	position.x = mask->rect.x + dif;
}

//Set the weapon
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
		if (lives < 3){
			++lives;
			App->audio->PlayFx(AUD_LIVE_UP);
		}
		if (truck < 3)
			++truck;
	}

	switch (state){
	case IDLE:
		switch (moving){
		case STRAIGHT:
			App->renderer->Blit(App->driver->graphics, position.x + rumble, position.y - velocity, &(idle.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
			break;
		case RIGHT:
			App->renderer->Blit(App->driver->graphics, position.x + rumble, position.y - velocity, &right, 1.0f, RENDER_PLAYER);
			break;
		case LEFT:
			App->renderer->Blit(App->driver->graphics, position.x + rumble, position.y - velocity, &left, 1.0f, RENDER_PLAYER);
			break;
		}
		break;
	case TURBO:
		App->renderer->Blit(App->driver->graphics, position.x, position.y - velocity, &turbo, 1.0f, RENDER_PLAYER);
		if (state_timer.GetTime() > 100)
			state = IDLE;
		break;
	}

	switch (weapon){
	case GUN:
		if (gun_turn)
			App->particles_top->addParticle(position.x + 13, position.y - STILE_SIZE / SCREEN_SIZE, ANIM_BULLET);
		else
			App->particles_top->addParticle(position.x + 21, position.y - STILE_SIZE, ANIM_BULLET);
		gun_turn = !gun_turn;
		weapon = WORKING;
		break;
	case OIL:
		App->particles_bottom->addParticle(position.x + 17, position.y + mask->rect.h, ANIM_OIL);
		weapon = WORKING;
		break;
	case SPRAY:
		App->particles_top->addParticle(position.x + 17, position.y + mask->rect.h, ANIM_SPRAY);
		weapon = WORKING;
		break;
	case ROCKET:
		App->particles_top->addParticle(position.x + 17, position.y - STILE_SIZE, ANIM_ROCKET);
		weapon = NONE;
		break;
	}

	last_position = position;

	if (lives == 0)
		App->road->SetGameState(G_OVER);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::OnColision(Collider* a, Collider *b)
{
	LOG("Collision Player");

	if (b->type == COL_PUDDLE){
		if (a->rect.x >= b->rect.x)
			SetMovement(RIGHT);
		else
			SetMovement(LEFT);
	}

	if (b->type == COL_ROAD_OUT || b->type == COL_BOMB){
		state = EXPLOTE;
		Dead();
	}

	if (b->type == COL_CAR || b->type == COL_ROAD_LORD){
		if (last_position.x == position.x){
			if (a->rect.y + a->rect.h + App->player->velocity  < b->rect.y
				|| a->rect.y + App->player->velocity  > b->rect.y + b->rect.h){
				state = EXPLOTE;
				Dead();
			}
		}
	}

	if (b->type == COL_ROAD_BORDER && App->player->velocity > 2){
		rumble = App->GetRand(30, -15);
	}

	return true;
}

//Acceleration
void ModulePlayer::UpGear(){

	if (App->GetTicks() % 10 == 0 && gear < 8 && !(gear == 0 && turbo_gear == 2)){
		gear += 1;
		state = TURBO;
		state_timer.Start();
	}
	velocity = gear * turbo_gear;
}

//Deceleration
void ModulePlayer::DownGear(){

	if (App->GetTicks() % 10 == 0 && gear > 0){
		gear -= 1;
	}
	velocity = gear * turbo_gear;
}

//Turbo On
void ModulePlayer::UpTurboGear(){
	turbo_gear = 2;
	velocity = gear * turbo_gear;
}

//Turbo Of
void ModulePlayer::DownTurboGear(){
	turbo_gear = 1;
	velocity = gear * turbo_gear;
}

//invencible mode
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
		idle.frames.push_back({ MTILE_SIZE * 0, (int)(MTILE_SIZE * 14.5), MTILE_SIZE, MTILE_SIZE });
		idle.frames.push_back({ MTILE_SIZE * 1, (int)(MTILE_SIZE * 14.5), MTILE_SIZE, MTILE_SIZE });

		right.y = MTILE_SIZE * 14.5;

		left.y = MTILE_SIZE * 14.5;
		mask->SetEnabled(false);
	}

	god_mode = !god_mode;
}

//Generate a random weapon
void ModulePlayer::GetRandWeapon(){
	if (truck > 0){
		--truck;
		int new_weapon = App->GetRand(6, 1);
		switch (new_weapon){
		case 1:
		case 2:
		case 3:
			App->player->oil = 99;

		}
		switch (new_weapon){
		case 4:
		case 5:
			App->player->spray = 49;

		}
		switch (new_weapon){
		case 6:
			App->player->rocket = 9;

		}
	}
}

//Player Dead
void ModulePlayer::Dead(){

	DownGear();
	if (App->road->road_state != G_OVER && App->road->road_state != G_PAUSE){
		App->particles_top->addParticle(mask->rect.x, mask->rect.y + mask->rect.h, ANIM_EXPLOTE);

		if ((first_mode >= 1000))
			--App->player->lives;

		velocity = 0;

		if (lives <= 0)
			App->road->road_state = G_OVER;
		else
			App->road->road_state = G_PAUSE;
	}
}

//resurrect
void ModulePlayer::Alive(){

	position.x = GetStartPosition();
	mask->rect.x = position.x + 21;
	App->road->road_state = G_PLAY;
	state = IDLE;
}

//Get the position where player have to appear
int ModulePlayer::GetStartPosition(){
	int res = 0;

	//positionate on thirth road line
	list<RoadLine*>::iterator start_line = App->road->screen.begin();
	++++start_line;

	for (vector<Collider*>::iterator it = (*start_line)->mask->begin(); it != (*start_line)->mask->end();){
		if ((*it)->type == COL_ROAD_BORDER){
			if ((*it)->rect.x > res){
				res = (*it)->rect.x;
				if ((*it)->rect.w == 2){
					res -= 16;
				}

			}
		}
		++it;
	}

	res -= RTILE_WIDTH;

	return res;
}

