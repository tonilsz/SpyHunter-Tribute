#ifndef __ROADLOOP_H__
#define __ROADLOOP_H__
#include "Globals.h"
#include "Point.h"
#include "RoadSegment.h"

#include <vector>
using namespace std;


enum SEGMENT_AMBIENT
{
	A_FOREST,
	A_DESERT,
	A_SNOW
};

#define LOOP1 vector<SEGMENT_TYPE>{ SEGMENT_FAT_A, SEGMENT_FAT_A, SEGMENT_CUR_LC}

class RoadLoop
{
public:
	vector<RoadSegment*> loop;
	SEGMENT_AMBIENT ambient;
	int pos;

	RoadLoop(vector<SEGMENT_TYPE>* loop_template, SEGMENT_AMBIENT ambient);

	~RoadLoop();

	void AddRoadSegment(RoadSegment *line);

	RoadSegment* GetCourrentSegment();

	void GenerateLoop(vector<SEGMENT_TYPE>* loop_template, const SEGMENT_AMBIENT &ambient);
	
	int GetSize();

private:
	void CleanLoop();
};

#endif // __ROADLOOP_H__