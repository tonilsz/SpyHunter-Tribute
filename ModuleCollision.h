#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Collider.h"

#include<vector>


class ModuleCollision : public Module
{
public:

	ModuleCollision(bool start_enabled = true);
	~ModuleCollision();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool Stop();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void AddColliderGroup(vector<Collider*>* mask);
	void DisplaceRoad();
	void DeleteBottomRoad();

	list<Collider*> colliders;
	bool matrix[COL_MAX][COL_MAX];
	bool debug_mode;

private:
	void CollisionTratement(Collider* c1, Collider* c2);
};

#endif // __ModuleCollision_H__