#include "Globals.h"
#include "Application.h"
#include "ModuleParticules.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"

ModuleParticules::ModuleParticules(bool start_enabled) : Module(start_enabled){

	particles = std::vector < pair<Particle*, Collider*>>();

}

ModuleParticules::~ModuleParticules()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModuleParticules::Start()
{
	LOG("Loading particules");

	App->particules->Enable();

	return true;
}

bool ModuleParticules::Init()
{
	LOG("Init particules");
	bool res = true;
	/*bool res = (graphics = App->player->graphics) == NULL;
	
	if (res)
		App->particules->Enable();
	*/

	return res;
}

// Unload assets
bool ModuleParticules::CleanUp()
{
	LOG("Unloading particules");

	for (vector<pair<Particle*, Collider*>>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		delete (*it).first;
	}
	//App->textures->Unload(graphics);
	//App->particules->Disable();

	return true;
}

// Update
update_status ModuleParticules::Update()
{
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
	return UPDATE_CONTINUE;
}

bool ModuleParticules::addParticle(float x, float y){
	pair<Particle*, Collider*> element;
	Particle *particle = new Particle;

	particle->pos = fPoint(x, y);

	particle->start = particle->pos;

	particle->live = Timer();

	particle->anim.frames.push_back({ 493, 1563, 43, 32 });
	particle->anim.frames.push_back({ 550, 1563, 56, 32 });
	particle->anim.frames.push_back({ 612, 1563, 28, 32 });
	particle->anim.frames.push_back({ 639, 1563, 28, 32 });
	particle->anim.frames.push_back({ 713, 1563, 28, 32 });

	particle->tex = App->player->graphics;

	particle->speed = 1.0f;

	particle->live.Start();

	Collider* mask = App->masks->AddCollider(SDL_Rect{ x, y, 56, 32 }, COLLIDER_HADOUKEN, this);

	particles.push_back(make_pair(particle, mask));
	return true;
}

bool ModuleParticules::deleteParticle(int id){
	pair<Particle*, Collider*> element;
	Particle *particle = new Particle;

	bool found = false;
	unsigned i = 0;
	for (i = 0; !found && i < particles.size(); ++i)
		if ((particles.begin() + i)->second->id == id)
			found = true;

	if (found)
		particles.erase(particles.begin() + --i);

	App->masks->eraseCollider(id);

	return found;
}

bool ModuleParticules::OnColision(Collider* a, Collider *b, COLISION_STATE status)
{
	LOG("Collision Particules");

	bool found = false;

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

	return found;
}