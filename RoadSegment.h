#ifndef __ROADSEGMENT_H__
#define __ROADSEGMENT_H__
#include "Globals.h"
#include "Point.h"
#include "RoadLine.h"

#include <vector>

using namespace std;

#define S_FAT_A_1 vector<SDL_Rect>{ T_GRASS, T_BUSH_A1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_GRASS }
#define S_FAT_A_2 vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_GRASS }
#define S_FAT_A_3 vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_A1, T_GRASS }
#define S_FAT_A_4 vector<SDL_Rect>{ T_GRASS, T_BUSH_B2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_B1, T_GRASS }

enum SEGMENT_TYPE
{
	SEGMENT_FAT_A,
	SEGMENT_FAT_B,
	SEGMENT_THIN_A,
	SEGMENT_THIN_B,
	SEGMENT_THIN_L,
	SEGMENT_THIN_R,
	SEGMENT_2_ROADS,
	SEGMENT_CUR_LC,
	SEGMENT_CUR_CR,
	SEGMENT_CUR_RC,
	SEGMENT_CUR_CL,
	SEGMENT_CLOSE,
	SEGMENT_OPEN,
	SEGMENT_BIFURCATION,
	SEGMENT_PRE_2_BRIDGES,
	SEGMENT_2_BRIDGES,
	SEGMENT_POST_2_BRIDGES,
	SEGMENT_END,
	SEGMENT_BRIDGE,
	SEGMENT_BRIDGE_L,
	SEGMENT_BRIDGE_R,
};

class RoadSegment
{
public:
	vector<RoadLine*> segment;
	int pos;

	RoadSegment(const SEGMENT_TYPE &type);
	
	~RoadSegment();

	void AddRoadLine(RoadLine* line);

	RoadLine* GetCourrentLine();

	void GenerateSegment(const SEGMENT_TYPE &type);

	int GetSize();

private:
	void CleanSegment();
};

#endif // __ROADSEGMENT_H__