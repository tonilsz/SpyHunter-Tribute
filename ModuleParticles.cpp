#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleDriver.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled){

	particles = std::vector < pair<Particle*, Collider*>>();
	background = std::vector < pair<Particle*, Collider*>>();

}

ModuleParticles::~ModuleParticles()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particules");

	App->particles->Enable();

	return true;
}

bool ModuleParticles::Resume()
{
	LOG("Init particules");
	bool res = true;

	graphics = App->textures->Load("efects.png");

	return res;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particules");

	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		delete (*it).first;
	}
	App->textures->Unload(graphics);
	App->particles->Disable();

	return true;
}

update_status ModuleParticles::PreUpdate()
{
	// Remove all colliders scheduled for deletion

	for (vector<pair<Particle*, Collider*>>::iterator it = background.begin(); it != background.end();)
	{
		it->first->live.Start();
		particles.push_back(*it);
		it = background.erase(it);
	}


	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end();)
	{
		if (!(*it).first->live.running)
		{
			RELEASE((*it).first);
			it = particles.erase(it);
		}
		else
		++it;
	}

	background.clear();

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleParticles::Update()
{

	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		it->first->pos.y += App->player->gear;
		it->second->rect.y = (int)it->first->pos.y - App->renderer->camera.y - (RTILE_HEIGHT * 1.5);


		switch (it->first->anim.type){
		case ANIM_BULLET:
			if (!it->first->anim.expired && it->first->live.GetTime() > 80){
				App->player->SetWeapon(NONE);
				it->first->anim.expired = true;
			}
			it->second->rect.y += (12 - App->player->gear);
			if (it->first->live.GetTime() < 30){
				it->first->pos.y -= App->player->gear + 4;
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
			}
			else{
				if (it->first->live.GetTime() > 800){
					(*it).first->live.Stop();
					App->masks->colliders.remove((*it).second);
					delete((*it).second);
				}
				else{
					it->first->pos.y -= App->player->gear + 4;
					if ((it->first->live.GetTime() % 100) < 50)
						App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
					else
						App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				}
			}
			break;
		case ANIM_OIL:
			if (!it->first->anim.expired && it->first->live.GetTime() > 20){
				App->player->SetWeapon(NONE);
				it->first->anim.expired = true;
			}
			if (it->first->live.GetTime() < 50)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 100)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 2000)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() > 2000){
				(*it).first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
			}
			break;
		case ANIM_SPRAY:
			if (!it->first->anim.expired && it->first->live.GetTime() > 80){
				App->player->SetWeapon(NONE);
				it->first->anim.expired = true;
			}

			it->second->rect.y += (12 - App->player->gear);

			if (it->first->live.GetTime() < 50)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 100){
				it->second->rect.y = it->first->pos.y + (STILE_SIZE / 2) - App->renderer->camera.y - (RTILE_HEIGHT * 1.5);
				it->second->rect.x = it->first->pos.x - (STILE_SIZE / 2);
				it->second->rect.w = STILE_SIZE * 2;
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			}
			else if (it->first->live.GetTime() < 150){
				it->second->rect.y = it->first->pos.y + (STILE_SIZE)-App->renderer->camera.y - (RTILE_HEIGHT * 1.5);
				it->second->rect.x = it->first->pos.x - (STILE_SIZE);
				it->second->rect.w = STILE_SIZE * 3;
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE), it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			}
			else if (it->first->live.GetTime() < 500){
				it->second->rect.y = it->first->pos.y + (STILE_SIZE * 1.5) - App->renderer->camera.y - (RTILE_HEIGHT * 1.5);
				it->second->rect.x = it->first->pos.x - (STILE_SIZE * 1.5);
				it->second->rect.w = STILE_SIZE * 4;
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE / 2), it->first->pos.y + (STILE_SIZE / 2), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE), it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE), it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE * 1.5), it->first->pos.y + (STILE_SIZE * 1.5), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x - (STILE_SIZE * 0.5), it->first->pos.y + (STILE_SIZE * 1.5), &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE * 0.5), it->first->pos.y + (STILE_SIZE * 1.5), &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE * 1.5), it->first->pos.y + (STILE_SIZE * 1.5), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			}
			else {
				(*it).first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
			}
			break;
		case ANIM_BULLET_ENEMY:
			//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
			break;
		case ANIM_ROCKET:
			it->first->pos.y -= App->player->gear + 4;
			if (it->first->live.GetTime() < 10)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 200)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 300)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 400)
				App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(3)), 1.0f, RENDER_OTHER);
			else if (it->first->live.GetTime() < 2000){
				it->second->SetEnabled(true);
				if ((it->first->live.GetTime() % 100) < 50)
					App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(4)), 1.0f, RENDER_OTHER);
				else
					App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetFrame(5)), 1.0f, RENDER_OTHER);
			}
			else if (it->first->live.GetTime() > 2000){
				it->first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
			}
			break;
		case ANIM_BOMB:
			------it->first->pos.y;
			------it->second->rect.y;

			if (((int)it->first->anim.current_frame % 2) == 0){
				App->renderer->Blit(graphics, it->second->rect.x - 13, it->first->pos.y, &(it->first->anim.GetCurrentFrame()), 1.0f, RENDER_OTHER);
				++it->first->anim.current_frame;
			}
			else{
				App->renderer->Blit(graphics, it->second->rect.x - 13, it->first->pos.y, &(it->first->anim.GetCurrentFrame()), 1.0f, RENDER_OTHER);
			}

			if (it->first->live.GetTime() > 500){
				it->first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
				App->driver->ClearWeapon();
				App->particles->addParticleBackground(it->first->pos.x, it->first->pos.y, ANIM_ROAD_HOLE);
			}

			break;
		case ANIM_EXPLOTE:
			App->renderer->Blit(graphics, it->second->rect.x - 13, it->first->pos.y, &(it->first->anim.GetCurrentFrame()), 1.0f, RENDER_OTHER);
			if (it->first->anim.Finished()){
				it->first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
			}
			break;
		case ANIM_ROAD_HOLE:
			if (it->first->anim.Finished())
				App->renderer->Blit(graphics, it->second->rect.x - 13, it->first->pos.y, &(it->first->anim.GetFrame(it->first->anim.frames.size() - 1)), 1.0f, RENDER_OTHER);
			else
				App->renderer->Blit(graphics, it->second->rect.x - 13, it->first->pos.y, &(it->first->anim.GetCurrentFrame()), 1.0f, RENDER_OTHER);
			break;
		case ANIM_PUDDLE:
				it->first->live.Start();
				if (it->first->live.running){
					App->renderer->Blit(graphics, it->first->pos.x - 32, it->first->pos.y, &((*it).first->anim.GetFrame(0)), 1.0f, RENDER_OTHER);
					App->renderer->Blit(graphics, it->first->pos.x + 32, it->first->pos.y, &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
					if (it->first->live.GetTime() < 200){
						it->first->live.Stop();
						App->masks->colliders.remove((*it).second);
						delete((*it).second);
					}
				}
				else {
					App->renderer->Blit(graphics, it->first->pos.x - 32, it->first->pos.y, &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
					App->renderer->Blit(graphics, it->first->pos.x + 32, it->first->pos.y, &((*it).first->anim.GetFrame(3)), 1.0f, RENDER_OTHER);
				}
			break;
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleParticles::addParticle(float x, float y, ANIMATION_TYPE type){
	pair<Particle*, Collider*>* element = add(x, y, type);
	if (type != COL_PUDDLE)
		element->first->live.Start();
	particles.push_back(*element);
	return true;
}

bool ModuleParticles::addParticleBackground(float x, float y, ANIMATION_TYPE type){
	pair<Particle*, Collider*>* element = add(x, y, type);
	background.push_back(*element);
	return true;
}


pair<Particle*, Collider*> * ModuleParticles::add(float x, float y, ANIMATION_TYPE type){

	Particle *particle = new Particle();

	particle->pos = fPoint(x, y);

	particle->start = particle->pos;

	particle->live = Timer();

	particle->anim.repeat = false;

	SDL_Rect col_area = SDL_Rect{ x, y, STILE_SIZE, STILE_SIZE };

	int total_frames = 3;
	COLLIDER_TYPE col_type = COL_NONE;

	switch (type){
	case ANIM_BULLET:
		App->audio->PlayFx(AUD_BULLET);
		col_type = COL_BULLET;
		col_area = SDL_Rect{ x + 16, y + 50, 2, 7 };
		break;
	case ANIM_SPRAY:
		App->audio->PlayFx(AUD_SPRAY);
		break;
	case ANIM_EXPLOTE:
		App->audio->PlayFx(AUD_EXPLOSION);
		total_frames = 5;
		col_type = COL_ROAD_OUT;
		break;
	case ANIM_BULLET_ENEMY:
		total_frames = 2;
		col_type = COL_BULLET_ENEMY;
		break;
	case ANIM_RAZOR:
		total_frames = 2;
		col_type = COL_BULLET_ENEMY;
		break;
	case ANIM_PUDDLE:
		total_frames = 4;
		col_type = COL_BULLET;
		break;
	case ANIM_ROAD_HOLE:
		App->audio->PlayFx(AUD_EXPLOSION);
		total_frames = 6;
		col_type = COL_ROAD_OUT;
		break;
	case ANIM_ROCKET:
		App->audio->PlayFx(AUD_ROCKET);
		total_frames = 6;
		col_type = COL_ROCKET;
		break;
	case ANIM_BOMB:
		App->audio->PlayFx(AUD_COPTER_BOMB);
		total_frames = 4;
		col_area = SDL_Rect{ x, y + 50, 6, 22 };
		break;
	}

	for (int i = 0; i < total_frames; ++i)
		particle->anim.frames.push_back({ STILE_SIZE * i, STILE_SIZE * type, STILE_SIZE, STILE_SIZE });
	particle->anim.speed = 0.2f;

	particle->anim.type = type;

	particle->speed = 1.0f;

	if (type == COL_PUDDLE)
		particle->anim.loop = false;

	Collider* mask = App->masks->AddCollider(col_area, col_type, App->particles);

	if (type == COL_ROCKET)
		mask->SetEnabled(false);

	pair<Particle*, Collider*> * res = new pair<Particle*, Collider*>(particle, mask);

	return res;
}

bool ModuleParticles::OnColision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Particules");

	bool found = false;

	/*
	if (status == COLISION_START){
		unsigned i = 0;
		for (i = 0; !found && i < particles.size(); ++i)
		if ((particles.begin() + i)->second->id == a->id)
			found = true;

		if (found){
			pair<Particle*, Collider*>* aux = &particles[--i];
			int res = 2840 - aux->first->live.GetTime();
			(particles[i]).first->killing = res;
		}
		App->masks->eraseCollider(a->id);
	}
	*/
	return found;
}