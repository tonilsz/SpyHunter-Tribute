#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled){

	particles = std::vector < pair<Particle*, Collider*>>();

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

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleParticles::Update()
{

	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		it->first->pos.y += App->player->gear;
		it->second->rect.y = (int)it->first->pos.y - App->renderer->camera.y - (RTILE_HEIGHT * 1.5);


		switch (it->second->type){
		case COL_BULLET:
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
		case COL_OIL:
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
		case COL_SPRAY:
			if (!it->first->anim.expired && it->first->live.GetTime() > 30){
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
				App->renderer->Blit(graphics, it->first->pos.x,					   it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(2)), 1.0f, RENDER_OTHER);
				App->renderer->Blit(graphics, it->first->pos.x + (STILE_SIZE), it->first->pos.y + (STILE_SIZE), &((*it).first->anim.GetFrame(1)), 1.0f, RENDER_OTHER);
			}
			else if (it->first->live.GetTime() < 2000){
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
		case COL_BULLET_ENEMY:
			//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
			break;
		case COL_ROCKET:
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
			} else if (it->first->live.GetTime() > 2000){
				it->first->live.Stop();
				App->masks->colliders.remove((*it).second);
				delete((*it).second);
			}
			break;
		case COL_BOMB:
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
			break;
		case COL_PUDDLE:
			//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
			break;
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleParticles::addParticle(float x, float y, ANIMATION_TYPE type){
	pair<Particle*, Collider*> element;
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
		col_type = COL_BULLET;
		col_area = SDL_Rect{ x + 16, y + 50, 2, 7 };
		break;
	case ANIM_EXPLOTE:
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
	case COL_PUDDLE:
		total_frames = 4;
		col_type = COL_BULLET;
		break;
	case ANIM_ROAD_HOLE:
		total_frames = 6;
		col_type = COL_ROAD_OUT;
		break;
	case ANIM_ROCKET:
		total_frames = 6;
		col_type = COL_ROCKET;
		col_area = SDL_Rect{ x + 14, y + 50, 5, 18 };
		break;
	case ANIM_BOMB:
		total_frames = 4;
		break;
	}

	for (int i = 0; i < total_frames; ++i)
		particle->anim.frames.push_back({ STILE_SIZE * i, STILE_SIZE * type, STILE_SIZE, STILE_SIZE });
	particle->anim.speed = 0.2f;


	particle->speed = 1.0f;

	if (type == COL_PUDDLE)
		particle->anim.loop = false;

	Collider* mask = App->masks->AddCollider(col_area, col_type, this);

	if (type == COL_ROCKET)
		mask->SetEnabled(false);

	particles.push_back(make_pair(particle, mask));
	return true;
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