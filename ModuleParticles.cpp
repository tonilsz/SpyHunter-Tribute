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

// Update
update_status ModuleParticles::Update()
{

	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		delete it->first;
		if (it->first->anim.Finished())
			App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetCurrentFrame()), 1.0f, RENDER_CAR);
		else
			App->renderer->Blit(graphics, it->first->pos.x, it->first->pos.y, &((*it).first->anim.GetCurrentFrame()), 1.0f, RENDER_CAR);
	}
	
	/*
	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		(*it).second->SetPos((*it).first->pos);
		App->masks->colliders;
		if ((*it).first->live.running == true){
			if ((*it).first->live.GetTime() < 2850 - (*it).first->killing){
				if ((((int)(*it).first->start.x - (int)(*it).first->pos.x) % 4) == 0)
					App->renderer->Blit((*it).first->tex, (int)(*it).first->pos.x, (int)(*it).first->pos.y, &((*it).first->anim.GetFrame(1)), (*it).first->speed);
				else if ((((int)(*it).first->start.x - (int)(*it).first->pos.x) % 2) == 0)
					App->renderer->Blit((*it).first->tex, (int)(*it).first->pos.x + 13, (int)(*it).first->pos.y, &((*it).first->anim.GetFrame(0)), (*it).first->speed);
			}
			else if ((*it).first->live.GetTime() < 2900 - (*it).first->killing){
				App->renderer->Blit((*it).first->tex, (int)(*it).first->pos.x + 28, (int)(*it).first->pos.y, &((*it).first->anim.GetFrame(2)), (*it).first->speed);
			}
			else if ((*it).first->live.GetTime() < 2950 - (*it).first->killing){
				App->renderer->Blit((*it).first->tex, (int)(*it).first->pos.x + 28, (int)(*it).first->pos.y, &((*it).first->anim.GetFrame(3)), (*it).first->speed);
			}
			else{
				App->renderer->Blit((*it).first->tex, (int)(*it).first->pos.x + 28, (int)(*it).first->pos.y, &((*it).first->anim.GetFrame(4)), (*it).first->speed);
			}
			if ((*it).first->live.GetTime() > 3000){
				(*it).first->live.Stop();				
				App->masks->eraseCollider((*it).second->id);//deleteParticle((*it).second->id);
			}
			++(*it).first->pos.x;
		}
	}
	*/

	/*

	switch (type){
	case COL_OIL:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(gun.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_SPRAY:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(oil.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_BULLET:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(spray.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_BULLET_ENEMY:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_ROCKET:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_BOMB:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_PUDDLE:
		App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	}*/
	return UPDATE_CONTINUE;
}

bool ModuleParticles::addParticle(float x, float y, COLLIDER_TYPE type){
	pair<Particle*, Collider*> element;
	Particle *particle = new Particle();

	particle->pos = fPoint(x, y);

	particle->start = particle->pos;

	particle->live = Timer();

	particle->anim.repeat = false;

	switch (type){
	case COL_BULLET:
		particle->anim.frames.push_back({ STILE_SIZE * OIL, STILE_SIZE * 0, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * OIL, STILE_SIZE * 1, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * OIL, STILE_SIZE * 2, STILE_SIZE, STILE_SIZE });
		particle->anim.speed = 0.2f;
		break;
	case COL_OIL:
		particle->anim.frames.push_back({ STILE_SIZE * GUN, STILE_SIZE * 0, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * GUN, STILE_SIZE * 1, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * GUN, STILE_SIZE * 2, STILE_SIZE, STILE_SIZE });
		particle->anim.speed = 0.2f;
		break;
	case COL_SPRAY:
		particle->anim.frames.push_back({ STILE_SIZE * SPRAY, STILE_SIZE * 0, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * SPRAY, STILE_SIZE * 1, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * SPRAY, STILE_SIZE * 2, STILE_SIZE, STILE_SIZE });
		particle->anim.speed = 0.2f; 
		break;
	case COL_BULLET_ENEMY:
		//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_ROCKET:
		particle->anim.frames.push_back({ STILE_SIZE * ROCKET, STILE_SIZE * 0, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * ROCKET, STILE_SIZE * 1, STILE_SIZE, STILE_SIZE });
		particle->anim.frames.push_back({ STILE_SIZE * ROCKET, STILE_SIZE * 2, STILE_SIZE, STILE_SIZE });
		particle->anim.speed = 0.2f;
		break;
	case COL_BOMB:
		//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	case COL_PUDDLE:
		//App->renderer->Blit(graphics, particle->pos.x, particle->pos.y - gear, &(rocket.GetCurrentFrame()), 1.0f, RENDER_PLAYER);
		break;
	}


	particle->speed = 1.0f;

	particle->live.Start();

	Collider* mask = App->masks->AddCollider(SDL_Rect{ x, y, STILE_SIZE, STILE_SIZE }, type, this);

	particles.push_back(make_pair(particle, mask));
	return true;
}

bool ModuleParticles::deleteParticle(int id){
	pair<Particle*, Collider*> element;
	Particle *particle = new Particle;

	bool found = false;
	/*
	unsigned i = 0;
	for (i = 0; !found && i < particles.size(); ++i)
		if ((particles.begin() + i)->second->id == id)
			found = true;

	if (found)
		particles.erase(particles.begin() + --i);

	App->masks->eraseCollider(id);
	*/
	return found;
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