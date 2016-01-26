#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "RoadLoop.h"

#include <vector>
using namespace std;

enum GAME_STATE{
	G_START,
	G_PAUSE,
	G_PLAY,
	G_OVER
};

enum LOOP_TYPE
{
	LOOP_0,
	LOOP_1,
	LOOP_2,
	LOOP_3,
	LOOP_4,
	LOOP_5,
	LOOP_6

};

struct SDL_Texture;

class ModuleRoad : public Module
{
public:
	ModuleRoad(bool start_enabled = true);
	~ModuleRoad();

	bool Start();
	bool Resume();
	update_status Update();
	bool Stop();

	void AddLine();
	void AmbientChange(SEGMENT_AMBIENT ambient = A_NONE);
	void SetGameState(GAME_STATE state = G_START);
	SEGMENT_TYPE GetCurrentSegmentType();
	int SetStartStatus();

	GAME_STATE road_state;
	SDL_Texture* graphics = nullptr;

	//Acutual position
	int pos_loop;
	int pos_segment;
	int pos_line;

	//puddle handler
	int next_puddle;

	//The Road is here
	vector<RoadLoop*> road;
	//What we have to print on screen
	list<RoadLine*> screen;

private:
	void GenerateLine();

};

#endif // __MODULESCENEKEN_H__