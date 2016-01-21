#include "Globals.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleRoad.h"
#include "Collider.h"

struct SDL_Texture;


ModuleCollision::ModuleCollision(bool start_enabled) : 
Module(start_enabled), 
debug_mode(true)
{
	for (int i = 0; i < COL_MAX; i++)
		for (int j = 0; j < COL_MAX; j++)
			matrix[i][j] = false;
	
	matrix[COL_CAR][COL_CAR] = true;
	matrix[COL_CAR][COL_PLAYER] = true;
	matrix[COL_CAR][COL_TRUCK] = true;
	matrix[COL_CAR][COL_ROAD_LORD] = true;
	matrix[COL_CAR][COL_OIL] = true;
	matrix[COL_CAR][COL_SPRAY] = true;
	matrix[COL_CAR][COL_BULLET] = true;
	matrix[COL_CAR][COL_ROAD_BORDER] = false;
	matrix[COL_CAR][COL_BOMB] = true;
	matrix[COL_CAR][COL_PUDDLE] = true;
	matrix[COL_CAR][COL_BULLET_ENEMY] = true;

	matrix[COL_CAR][COL_CAR] = true;
	matrix[COL_CAR][COL_TRUCK] = true;
	matrix[COL_CAR][COL_ROAD_LORD] = true;
	matrix[COL_CAR][COL_ROAD_OUT] = true;
	matrix[COL_CAR][COL_ROAD_BORDER] = true;
	matrix[COL_CAR][COL_BOMB] = true;
	matrix[COL_CAR][COL_PUDDLE] = true;
	matrix[COL_CAR][COL_BULLET_ENEMY] = true;

	matrix[COL_TRUCK][COL_CAR] = true;
	matrix[COL_TRUCK][COL_PLAYER] = true;
	matrix[COL_TRUCK][COL_TRUCK] = true;
	matrix[COL_TRUCK][COL_ROAD_LORD] = true;
	matrix[COL_TRUCK][COL_OIL] = true;
	matrix[COL_TRUCK][COL_SPRAY] = true;
	matrix[COL_TRUCK][COL_BULLET] = true;
	matrix[COL_TRUCK][COL_ROAD_BORDER] = true;
	matrix[COL_TRUCK][COL_BOMB] = true;
	matrix[COL_TRUCK][COL_PUDDLE] = true;
	matrix[COL_TRUCK][COL_BULLET_ENEMY] = true;

	matrix[COL_ROAD_LORD][COL_CAR] = true;
	matrix[COL_ROAD_LORD][COL_PLAYER] = true;
	matrix[COL_ROAD_LORD][COL_TRUCK] = true;
	matrix[COL_ROAD_LORD][COL_ROAD_LORD] = true;
	matrix[COL_ROAD_LORD][COL_OIL] = true;
	matrix[COL_ROAD_LORD][COL_SPRAY] = true;
	matrix[COL_ROAD_LORD][COL_BULLET] = true;
	matrix[COL_ROAD_LORD][COL_ROAD_BORDER] = true;
	matrix[COL_ROAD_LORD][COL_BOMB] = true;
	matrix[COL_ROAD_LORD][COL_PUDDLE] = true;
	matrix[COL_ROAD_LORD][COL_BULLET_ENEMY ] = true;

	matrix[COL_MAD_BOMBER][COL_ROCKET] = true;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

//  Init assets
bool ModuleCollision::Start()
{
	LOG("Init collision module");

	return true;
}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); )
		{
			if ((*it)->to_delete == true)
			{
				RELEASE(*it);
				it = colliders.erase(it);
			}
			else if ((*it)->to_erase == true)
			{
				(*it)->rect.y -= 9 * RTILE_HEIGHT;
				(*it)->to_erase = false;
				it = colliders.erase(it);
			}
			else
				++it;
		}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{	
		Collider* c1;
		Collider* c2;


		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
		{
			c1 = *it;

			for (list<Collider*>::iterator it2 = ++it; it2 != colliders.end(); ++it2)
			{
				c2 = *it2;

				if (c1->CheckCollision(c2->rect) == true)
				{
					CollisionTratement(c1, c2);
					CollisionTratement(c2, c1);

				}
			}
		}
	
	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::PostUpdate()
{
	if (debug_mode == true)
	{
		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		{
			Collider* col = *it;
			if (col->enabled){
				Uint8 alpha = 100;
				switch (col->type)
				{
				case COL_NONE:
					App->renderer->Shadow(col->rect, 255, 255, 255, alpha);
					break;
				case COL_CAR:
				case COL_TRUCK:
				case COL_ROAD_LORD:
					App->renderer->Shadow(col->rect, 0, 0, 255, alpha);
					break;
				case COL_PLAYER:
					App->renderer->Shadow(col->rect, 0, 255, 0, alpha);
					break;
				case COL_MAD_BOMBER:
					App->renderer->Shadow(col->rect, 255, 0, 0, alpha);
					break;
				case COL_ROAD_OUT:
					App->renderer->Shadow(col->rect, 255, 255, 0, alpha);
					break;
				case COL_ROAD_BORDER:
					App->renderer->Shadow(col->rect, 0, 255, 255, alpha);
					break;
				case COL_PUDDLE:
					App->renderer->Shadow(col->rect, 0, 0, 0, alpha);
					break;
				case COL_OIL:
				case COL_SPRAY:
				case COL_BULLET:
				case COL_ROCKET:
					App->renderer->Shadow(col->rect, 255, 255, 255, alpha);
					break;
				case COL_BULLET_ENEMY:
				case COL_BOMB:
					App->renderer->Shadow(col->rect, 255, 128, 255, alpha);
					break;
				}
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCollision::Stop()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);

	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret);
	return ret;
}

void ModuleCollision::AddColliderGroup(vector<Collider*>* mask)
{
	for (vector<Collider*>::iterator it = mask->begin(); it != mask->end(); ++it)
		colliders.push_back(*it);
}

void ModuleCollision::CollisionTratement(Collider* c1, Collider* c2){
	if (c1->enabled && c2->enabled){
		if (matrix[c1->type][c2->type] && c1->callback){
			if (!c1->IsCollising(c2)){
				c1->AddCollision(c2);
				c1->callback->OnColision(c1, c2, COL_START);
			}
			else
				c1->callback->OnColision(c1, c2, COL_DURING);
		}
		else {
			c1->RemoveCollision(c2);
			c1->callback->OnColision(c1, c2, COL_END);
		}
	}
}

void ModuleCollision::DisplaceRoad(){

	for (list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		(*it)->rect.y += RTILE_HEIGHT;

}

void ModuleCollision::DeleteBottomRoad(){

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->rect.y >= (RTILE_HEIGHT) * 9 && ((*it)->type == COL_ROAD_OUT || (*it)->type == COL_ROAD_BORDER))
			(*it)->to_erase = true;

}

