#ifndef __MODULEPARTICULES_H__
#define __MODULEPARTICULES_H__
#include "Module.h"
#include "Animation.h"
#include "Timer.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

/*struct particle{ 
	fPoint pos;
	Timer live;
	Animation anim;
	Vector scale;
	SDL_Texture tex;
	fPoint speed;
	status;
	Color tintado;
	fPoint accel;
	bool visible;
	fx start;
	fx update;
	float rotation;
	float rot_speed;
	float rot_accel;
};*/

struct Particle{
	fPoint pos;
	fPoint start;
	Timer live;
	Animation anim;
	SDL_Rect test;
	SDL_Texture* tex = nullptr;
	float speed;
	int killing = 0;
};

class ModuleParticules : public Module
{
public:
	ModuleParticules(bool start_enabled = true);
	~ModuleParticules();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();
	bool addParticle(float x, float y);
	bool deleteParticle(int id);
	bool OnColision(Collider* a, Collider *b, COLISION_STATE status);

	std::vector<pair<Particle*, Collider*>> particles;
};

#endif // __MODULEPARTICULES_H__