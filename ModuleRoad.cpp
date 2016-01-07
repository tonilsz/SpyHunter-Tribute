#include "Globals.h"
#include "Application.h"
#include "ModuleRoad.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleDriver.h"
#include "RoadLoop.h"
#include "RoadSegment.h"
#include "RoadLine.h"
#include "SDL/include/SDL.h"

ModuleRoad::ModuleRoad(bool start_enabled) : 
Module(start_enabled), 
pos_loop(0),
pos_segment(0),
pos_line(0)
{
}

ModuleRoad::~ModuleRoad()
{}

// Load assets
bool ModuleRoad::Start()
{
	LOG("Loading Road scene");

	road.push_back(new RoadLoop(new LOOP1, (SEGMENT_AMBIENT)A_FOREST));

	graphics = App->textures->Load("scene.png");

	App->player->Enable();

	return graphics != NULL;
}

// Resume assets
bool ModuleRoad::Resume()
{
	LOG("Resume Road scene");

	int i = 0;

	for (; i < 9; ++i){
		GenerateLine();
		if (i!=8)
			App->masks->DisplaceRoad();
	}
	return i == 9;
}

// UnLoad assets
bool ModuleRoad::Stop()
{
	LOG("Unloading Road scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw Road
update_status ModuleRoad::Update()
{	
	int i = 0, j = 0;
	for (list<RoadLine*>::reverse_iterator it_line = screen.rbegin(); it_line != screen.rend(); ++it_line, ++i)
		for (j = 0; j < 15; j++)
			App->renderer->Blit(graphics, 0 + (j * 32), 0 + (i * 64), ((*it_line)->GetCourrentTile()), 1.0f, RENDER_ROAD);

	return i == 9 && j == 15 ? UPDATE_CONTINUE : UPDATE_ERROR;
}

void ModuleRoad::AddLine(){
	screen.pop_front();
	App->masks->DisplaceRoad();
	App->masks->DeleteBottomRoad();

	GenerateLine();

}

void ModuleRoad::GenerateLine(){

	RoadLine *ptr_line = road.begin()[pos_loop]->loop.begin()[pos_segment]->segment.begin()[pos_line];
	screen.push_back(ptr_line);
	if (ptr_line->mask!=NULL)
		App->masks->AddColliderGroup(ptr_line->mask);

	++pos_line;
	if (pos_line == road.begin()[pos_loop]->loop.begin()[pos_segment]->segment.size()){
		pos_line = 0;
		++pos_segment;
		if (pos_segment == road.begin()[pos_loop]->loop.size()){
			pos_segment = 0;
			++pos_loop;
			if (pos_loop == road.size()){
				pos_loop = 0;
			}
		}
	}
}