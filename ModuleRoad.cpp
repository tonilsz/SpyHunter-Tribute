#include "Globals.h"
#include "Application.h"
#include "ModuleRoad.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleDriver.h"
#include "ModuleUI.h"
#include "ModuleParticles.h"
#include "RoadLoop.h"
#include "RoadSegment.h"
#include "RoadLine.h"
#include "SDL/include/SDL.h"

ModuleRoad::ModuleRoad(bool start_enabled) : 
Module(start_enabled), 
pos_loop(0),
pos_segment(0),
pos_line(0),
road_state(G_START),
next_puddle(0)
{
}

ModuleRoad::~ModuleRoad()
{}

// Load assets
bool ModuleRoad::Start()
{
	LOG("Loading Road scene");
	//Test Road
	//road.push_back(new RoadLoop(new LOOP0, (SEGMENT_AMBIENT)A_SNOW));

	//True Loop
	road.push_back(new RoadLoop(new LOOP1, (SEGMENT_AMBIENT)A_FOREST));
	road.push_back(new RoadLoop(new LOOP2, (SEGMENT_AMBIENT)A_DESERT));
	road.push_back(new RoadLoop(new LOOP3, (SEGMENT_AMBIENT)A_GREY));
	road.push_back(new RoadLoop(new LOOP4, (SEGMENT_AMBIENT)A_FOREST));
	road.push_back(new RoadLoop(new LOOP5, (SEGMENT_AMBIENT)A_GREY));
	road.push_back(new RoadLoop(new LOOP6, (SEGMENT_AMBIENT)A_GREEN));

	road.push_back(new RoadLoop(new LOOP1, (SEGMENT_AMBIENT)A_FOREST));
	road.push_back(new RoadLoop(new LOOP2, (SEGMENT_AMBIENT)A_DESERT));
	road.push_back(new RoadLoop(new LOOP3, (SEGMENT_AMBIENT)A_GREY));
	road.push_back(new RoadLoop(new LOOP4, (SEGMENT_AMBIENT)A_FOREST));
	road.push_back(new RoadLoop(new LOOP5, (SEGMENT_AMBIENT)A_GREY));
	road.push_back(new RoadLoop(new LOOP6, (SEGMENT_AMBIENT)A_GREEN));

	road.push_back(new RoadLoop(new LOOP7, (SEGMENT_AMBIENT)A_SNOW));

	graphics = App->textures->Load("amb_forest.png");

	App->player->Enable();

	SetStartStatus();

	return graphics != NULL;
}

// Resume assets
bool ModuleRoad::Resume()
{
	LOG("Resume Road scene");

	App->player->Enable();

	App->audio->PlayMusic("title-song.mid", 1);

	return true;
}

// UnLoad assets
bool ModuleRoad::Stop()
{
	LOG("Unloading Road scene");

	for (vector<RoadLoop*>::iterator it = road.begin(); it != road.end(); ++it){
		(*it)->CleanLoop();
		RELEASE(*it);
	}

	road.clear();

	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw Road
update_status ModuleRoad::Update()
{	
	//Lunch random puddle
	if (next_puddle == App->GetTicks()){
		next_puddle += App->GetRand(500, 100);
		App->particles_bottom->addParticle(ModuleCars::SetCarStartPosition(true), 0, ANIM_PUDDLE);
	}

	int i = 0, j = 0;
	for (list<RoadLine*>::reverse_iterator it_line = screen.rbegin(); it_line != screen.rend(); ++it_line, ++i)
		for (j = 0; j < 15; j++)
			App->renderer->Blit(graphics, 0 + (j * 32), 0 + (i * 64), ((*it_line)->GetCourrentTile()), 1.0f, RENDER_ROAD);

	return i == 9 && j == 15 ? UPDATE_CONTINUE : UPDATE_ERROR;
}

// Add new line to the screen and delete the bottom line
void ModuleRoad::AddLine(){
	screen.pop_front();
	App->masks->DisplaceRoad();
	App->masks->DeleteBottomRoad();

	GenerateLine();

}

//Generates the next line of the road
void ModuleRoad::GenerateLine(){

	RoadLine *ptr_line = road.begin()[pos_loop]->loop.begin()[pos_segment]->segment.begin()[pos_line];
	screen.push_back(ptr_line);
	if (ptr_line->mask!=NULL)
		App->masks->AddColliderGroup(ptr_line->mask);

	++pos_line;
	if (pos_line == road.begin()[pos_loop]->loop.begin()[pos_segment]->segment.size()){
		pos_line = 0;
		++pos_segment;
		if (pos_segment == 2)
			//On change loop
			AmbientChange();
		if (pos_segment == road.begin()[pos_loop]->loop.size()){
			pos_segment = 0;
			++pos_loop;
			if (pos_loop == road.size()){
				pos_loop = 0;
			}
		}
	}
}

//Change the ambient of the road and increase dificulty
void ModuleRoad::AmbientChange(SEGMENT_AMBIENT ambient){
	//increase boombs throwed by copter
	++App->driver->seek_max;

	//Get a new truck item
	++App->player->truck;

	// increase car generation handler
	if (App->driver->car_generation_handler > 160)
		App->driver->car_generation_handler -= 20;

	if (ambient == A_NONE)
		ambient = road.begin()[pos_loop]->ambient;

	//reload texture
	App->textures->Unload(graphics);
	App->ui->textColor = WHITE;
	switch (ambient){
		case A_FOREST:
			graphics = App->textures->Load("amb_forest.png");
			break;
		case A_DESERT:
			graphics = App->textures->Load("amb_desert.png");
			break;
		case A_GREY:
			graphics = App->textures->Load("amb_green.png");
			break;
		case A_GREEN:
			graphics = App->textures->Load("amb_grey.png");
			break;
		case A_SNOW:
			graphics = App->textures->Load("amb_snow.png");
			App->ui->textColor = BLUE;
			break;
	}

}

//Change the state of the game
void ModuleRoad::SetGameState(GAME_STATE state){
	if (road_state == G_START){
		if (state == G_PLAY){
			road_state = state;			
			next_puddle = App->GetTicks() + App->GetRand(500, 100);
		}
	}
	else if (road_state == G_PLAY){
		if (state == G_OVER){
			road_state = state;
		}
	}
	else if (road_state == G_OVER){
		if (state == G_PLAY){
			road_state = state;

			//Set all the values like the start and generate some cars

			for (int i = 0; i < 6; ++i)
				App->driver->AddCar(App->driver->GetRandomCar());

			App->driver->car_generation_handler = 300;
			AmbientChange(A_FOREST);
			SetStartStatus();
			App->player->oil = 0;
			App->player->spray = 0;
			App->player->rocket = 0;
			App->player->truck = 0;
			App->player->score = 0;
			App->player->lives = 1;
			App->player->pos = 0;
			App->player->first_mode = 0;
			App->player->position.x = RTILE_WIDTH * 11;
			App->player->mask->rect.x = App->player->position.x + 21;
			App->player->state = IDLE;
			App->renderer->camera.y = -1.5 * RTILE_HEIGHT * SCREEN_SIZE;
			App->driver->seek_max = 3;
			for (int i = 0; i < 6; ++i){
				App->driver->AddCar(App->driver->GetRandomCar());
			}
			next_puddle = App->GetTicks() + App->GetRand(500, 100);
			App->particles_top->DeleteParticles();
			App->particles_bottom->DeleteParticles();

		}
	}
}

//Get the road segment type of current segment
SEGMENT_TYPE ModuleRoad::GetCurrentSegmentType(){
	return road.begin()[pos_loop]->loop.begin()[pos_segment]->type;
}

// Put the road on start
int ModuleRoad::SetStartStatus(){
	pos_line = pos_segment = pos_loop = 0;
	road_state = G_START;

	int i = 0;

	for (; i < 9; ++i){
		GenerateLine();
		if (i != 8)
			App->masks->DisplaceRoad();
	}

	while (screen.size() > 9){
		screen.pop_front();
		App->masks->DisplaceRoad();
		App->masks->DeleteBottomRoad();
	}
	return i == 9;
}