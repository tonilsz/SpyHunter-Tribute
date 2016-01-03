#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "RoadLoop.h"

#include <vector>
using namespace std;

enum LOOP_TYPE
{
	LOOP_1,
	LOOP_2

};

struct SDL_Texture;

#define LOOP1 vector<SEGMENT_TYPE>{ SEGMENT_FAT_A, SEGMENT_FAT_A, SEGMENT_FAT_A}

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

	SDL_Texture* graphics = nullptr;
	int pos_loop;
	int pos_segment;
	int pos_line;
	vector<RoadLoop*> road;
	list<RoadLine*> screen;

private:
	void GenerateLine();

};

#endif // __MODULESCENEKEN_H__