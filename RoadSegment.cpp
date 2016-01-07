#include "RoadSegment.h"
#include "Collider.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRoad.h"

RoadSegment::RoadSegment(const SEGMENT_TYPE &type):
pos(0)
{
	GenerateSegment(type);
}

RoadSegment::~RoadSegment(){
	CleanSegment();
}

void RoadSegment::AddRoadLine(RoadLine* line){
	segment.push_back(line);
}

RoadLine* RoadSegment::GetCourrentLine(){
	RoadLine* res = ((segment)[pos]);
	++pos;
	if (pos >= segment.size()) pos = 0;
	return res;
}

void RoadSegment::GenerateSegment(const SEGMENT_TYPE &type){
	CleanSegment();

	//generate new road
	switch (type){
	case SEGMENT_FAT_A:
		segment.push_back(new RoadLine(new S_FAT_A_1, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_2, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_3, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_4, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_1, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_2, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_3, new C_FAT));
		segment.push_back(new RoadLine(new S_FAT_A_4, new C_FAT));
		break;
	case SEGMENT_CUR_LC:
		segment.push_back(new RoadLine(new S_CUR_LC_1, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_2, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_3, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_4, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_5, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_6, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_7, NULL));
		segment.push_back(new RoadLine(new S_CUR_LC_8, NULL));
		break;
	/*
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
	SEGMENT_THIN:
		break;
	case SEGMENT_CUR_LC:
		break;
	case SEGMENT_CUR_CR:
		break;
	case SEGMENT_CUR_RC:
		break;
	case SEGMENT_CUR_CL:
		break;
	case SEGMENT_CLOSE:
		break;
	case SEGMENT_OPEN:
		break;
	case SEGMENT_BRIDGE:
		break;
	case SEGMENT_BIFURCATION:
		break;
	case SEGMENT_2_ROADS:
		break;
	case SEGMENT_PRE_2_BRIDGES:
		break;
	case SEGMENT_2_BRIDGES:
		break;
	case SEGMENT_POST_2_BRIDGES:
		break;
	case SEGMENT_END:
		break;*/
	default:
		LOG("RoadSegment - Cannot generate segment %s\n", type);
	}
}

int RoadSegment::GetSize(){
	return segment.size();
}

void RoadSegment::CleanSegment(){

	for (vector<RoadLine*>::iterator it = segment.begin(); it != segment.end(); ++it)
		delete(*it);
	segment.clear();
}