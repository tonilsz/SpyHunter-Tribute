#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleRoad.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 110;

	last_position = position;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	foward.frames.push_back({ 5, 129, 66, 92 });
	foward.frames.push_back({ 75, 128, 66, 92 });
	foward.frames.push_back({ 162, 129, 66, 92 });
	foward.frames.push_back({ 259, 127, 66, 92 });
	foward.frames.push_back({ 347, 127, 66, 92 });
	foward.frames.push_back({ 427, 128, 66, 92 });
	foward.speed = 0.1f;

	// idle animation (arcade sprite sheet)
	hado.frames.push_back({ 34, 1545, 100, 90 });
	hado.frames.push_back({ 135, 1545, 108, 90 });
	hado.frames.push_back({ 244, 1545, 112, 90 });
	hado.frames.push_back({ 357, 1545, 106, 90 });
	hado.speed = 0.2f;

	// idle animation (arcade sprite sheet)
	jump.frames.push_back({ 17, 799, 82, 134 });
	jump.frames.push_back({ 100, 799, 75, 129 });
	jump.frames.push_back({ 176, 799, 50, 104 });
	jump.frames.push_back({ 251, 799, 54, 77 });
	jump.frames.push_back({ 327, 799, 48, 85 });
	jump.frames.push_back({ 397, 799, 48, 101 });
	jump.frames.push_back({ 464, 799, 55, 129 });
	jump.speed = 0.2f;

	// win animation (arcade sprite sheet)
	won.frames.push_back({ 495, 2440, 53, 122 });
	won.frames.push_back({ 573, 2440, 60, 122 });
	won.frames.push_back({ 660, 2440, 60, 122 });
	won.frames.push_back({ 745, 2440, 55, 122 });
	won.speed = 0.2f;

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load Colliders
bool ModulePlayer::Init()
{
	LOG("Init player");

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	mask = App->masks->AddCollider(SDL_Rect{ position.x, position.y, 60, 90 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	
	return App->masks->eraseCollider(mask->id);
}


update_status ModulePlayer::PreUpdate()
{
	if (last_position.x == position.x)
		moving = IDLE;
	else if (last_position.x < position.x)
		moving = FOWARD;
	else if (last_position.x > position.x)
		moving = BACKWARD;

	last_position = position;
	return UPDATE_CONTINUE;
}

void ModulePlayer::SetState(int new_state){
	if (state != HADOUKEN && state != JUMP && state != WON){
		state = new_state;
		if (state == JUMP)
			jump_live.Start();
		if (state == HADOUKEN)
			hado_live.Start();
		if (state == WON)
			won_live.Start();
	}

}

void ModulePlayer::SetMovement(int new_state){
	if (state != HADOUKEN && state != WON){
		moving = new_state;
		if (moving == FOWARD){
			++position.x;
			int width = App->scene_ken->ground.w - 200;
			if (!App->scene_ken->IsEnabled())
				width = App->scene_honda->ground.w - 300;
			if (position.x > width){
				position.x = width;
			}
			//if (App->player->position.x > (App->window->screen_surface->w -20))
		}
		else
			--position.x;
			if (position.x < 0)
				position.x = 0;

		mask->SetPos(position);
	}

}

update_status ModulePlayer::Update()
{
	switch (state){
	case IDLE:
		switch (moving){
		case IDLE:
			App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 0.75f);
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
		if (jump_live.running == true){
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
				App->particules->addParticle(App->player->position.x + App->player->hado.GetFrame(3).w,
					App->player->position.y + 18);
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
				App->scene_honda->win = false;
				App->particules->addParticle(App->player->position.x + App->player->won.GetFrame(3).w,
					App->player->position.y + 18);
			}

		}
		else{
			state = IDLE;
		}
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