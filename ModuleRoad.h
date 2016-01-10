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