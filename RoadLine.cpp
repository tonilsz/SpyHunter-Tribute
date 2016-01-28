#include "RoadLine.h"

RoadLine::RoadLine(vector<SDL_Rect>* line, vector<Collider*>* mask) :
line(line),
mask(mask),
pos(0)
{}

RoadLine::~RoadLine(){
}

//Set a specific tile in line pos
void RoadLine::SetTile(int pos,const SDL_Rect &tile)
{
	if (pos < 15){
		(*line)[pos] = tile;
	}else{
		LOG("RoadLine - Cannot add tile in pos %s\n", pos);
	}
}

//Get current Tile
SDL_Rect* RoadLine::GetCourrentTile(){
	SDL_Rect* res = &((*line)[pos]);
	++pos;
	if (pos > 14) pos = 0;
	return res;
}

void RoadLine::CleanLine(){
	if (mask != NULL){
		/*for (vector<Collider*>::iterator it = mask->begin(); it != mask->end(); ++it){
			RELEASE(*it);
			App->mask->DropCollider();
		}*/

		mask->clear();
		RELEASE(mask);
	}

	if (line != NULL){
		line->clear();
		RELEASE(line);
	}
}