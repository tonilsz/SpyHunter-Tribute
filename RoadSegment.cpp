#include "RoadSegment.h"
#include "Collider.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRoad.h"

RoadSegment::RoadSegment(const SEGMENT_TYPE &type) :
pos(0),
type(type)
{
	GenerateSegment(type);
}

RoadSegment::~RoadSegment(){
	CleanSegment();
}

//Generate specific Road Segment
void RoadSegment::GenerateSegment(const SEGMENT_TYPE &type){
	CleanSegment();

	//generate new road
	switch (type){
	case S_FAT_A:
		segment.push_back(GenerateSegmentLine(S_FAT_A_1));
		segment.push_back(GenerateSegmentLine(S_FAT_A_2));
		segment.push_back(GenerateSegmentLine(S_FAT_A_3));
		segment.push_back(GenerateSegmentLine(S_FAT_A_4));
		segment.push_back(GenerateSegmentLine(S_FAT_A_5));
		segment.push_back(GenerateSegmentLine(S_FAT_A_6));
		segment.push_back(GenerateSegmentLine(S_FAT_A_7));
		segment.push_back(GenerateSegmentLine(S_FAT_A_8));
		break;
	case S_FAT_B:
		segment.push_back(GenerateSegmentLine(S_FAT_B_1));
		segment.push_back(GenerateSegmentLine(S_FAT_B_2));
		segment.push_back(GenerateSegmentLine(S_FAT_B_3));
		segment.push_back(GenerateSegmentLine(S_FAT_B_4));
		segment.push_back(GenerateSegmentLine(S_FAT_B_5));
		segment.push_back(GenerateSegmentLine(S_FAT_B_6));
		segment.push_back(GenerateSegmentLine(S_FAT_B_7));
		segment.push_back(GenerateSegmentLine(S_FAT_B_8));
		break;

	case S_THIN_A:
		segment.push_back(GenerateSegmentLine(S_THIN_A_1));
		segment.push_back(GenerateSegmentLine(S_THIN_A_2));
		segment.push_back(GenerateSegmentLine(S_THIN_A_3));
		segment.push_back(GenerateSegmentLine(S_THIN_A_4));
		segment.push_back(GenerateSegmentLine(S_THIN_A_5));
		segment.push_back(GenerateSegmentLine(S_THIN_A_6));
		segment.push_back(GenerateSegmentLine(S_THIN_A_7));
		segment.push_back(GenerateSegmentLine(S_THIN_A_8));
		break;
	case S_THIN_B:
		segment.push_back(GenerateSegmentLine(S_THIN_B_1));
		segment.push_back(GenerateSegmentLine(S_THIN_B_2));
		segment.push_back(GenerateSegmentLine(S_THIN_B_3));
		segment.push_back(GenerateSegmentLine(S_THIN_B_4));
		segment.push_back(GenerateSegmentLine(S_THIN_B_5));
		segment.push_back(GenerateSegmentLine(S_THIN_B_6));
		segment.push_back(GenerateSegmentLine(S_THIN_B_7));
		segment.push_back(GenerateSegmentLine(S_THIN_B_8));
		break;
	case S_THIN_L:
		segment.push_back(GenerateSegmentLine(S_THIN_L_1));
		segment.push_back(GenerateSegmentLine(S_THIN_L_2));
		segment.push_back(GenerateSegmentLine(S_THIN_L_3));
		segment.push_back(GenerateSegmentLine(S_THIN_L_4));
		segment.push_back(GenerateSegmentLine(S_THIN_L_5));
		segment.push_back(GenerateSegmentLine(S_THIN_L_6));
		segment.push_back(GenerateSegmentLine(S_THIN_L_7));
		segment.push_back(GenerateSegmentLine(S_THIN_L_8));
		break;
	case S_THIN_R:
		segment.push_back(GenerateSegmentLine(S_THIN_R_1));
		segment.push_back(GenerateSegmentLine(S_THIN_R_2));
		segment.push_back(GenerateSegmentLine(S_THIN_R_3));
		segment.push_back(GenerateSegmentLine(S_THIN_R_4));
		segment.push_back(GenerateSegmentLine(S_THIN_R_5));
		segment.push_back(GenerateSegmentLine(S_THIN_R_6));
		segment.push_back(GenerateSegmentLine(S_THIN_R_7));
		segment.push_back(GenerateSegmentLine(S_THIN_R_8));
		break;

	case S_2_ROADS:
		segment.push_back(GenerateSegmentLine(S_2_ROADS_1));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_2));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_3));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_4));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_5));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_6));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_7));
		segment.push_back(GenerateSegmentLine(S_2_ROADS_8));
		break;

	case S_CUR_LC:
		segment.push_back(GenerateSegmentLine(S_CUR_LC_1));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_2));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_3));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_4));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_5));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_6));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_7));
		segment.push_back(GenerateSegmentLine(S_CUR_LC_8));
		break;
	case S_CUR_CR:
		segment.push_back(GenerateSegmentLine(S_CUR_CR_1));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_2));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_3));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_4));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_5));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_6));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_7));
		segment.push_back(GenerateSegmentLine(S_CUR_CR_8));
		break;
	case S_CUR_RC:
		segment.push_back(GenerateSegmentLine(S_CUR_RC_1));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_2));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_3));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_4));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_5));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_6));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_7));
		segment.push_back(GenerateSegmentLine(S_CUR_RC_8));
		break;
	case S_CUR_CL:
		segment.push_back(GenerateSegmentLine(S_CUR_CL_1));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_2));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_3));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_4));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_5));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_6));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_7));
		segment.push_back(GenerateSegmentLine(S_CUR_CL_8));
		break;

	case S_CLOSE:
		segment.push_back(GenerateSegmentLine(S_CLOSE_1));
		segment.push_back(GenerateSegmentLine(S_CLOSE_2));
		segment.push_back(GenerateSegmentLine(S_CLOSE_3));
		segment.push_back(GenerateSegmentLine(S_CLOSE_4));
		segment.push_back(GenerateSegmentLine(S_CLOSE_5));
		segment.push_back(GenerateSegmentLine(S_CLOSE_6));
		segment.push_back(GenerateSegmentLine(S_CLOSE_7));
		segment.push_back(GenerateSegmentLine(S_CLOSE_8));
		segment.push_back(GenerateSegmentLine(S_CLOSE_9));
		segment.push_back(GenerateSegmentLine(S_CLOSE_10));
		segment.push_back(GenerateSegmentLine(S_CLOSE_11));
		segment.push_back(GenerateSegmentLine(S_CLOSE_12));
		segment.push_back(GenerateSegmentLine(S_CLOSE_13));
		segment.push_back(GenerateSegmentLine(S_CLOSE_14));
		segment.push_back(GenerateSegmentLine(S_CLOSE_15));
		break;

	case S_OPEN:
		segment.push_back(GenerateSegmentLine(S_OPEN_1));
		segment.push_back(GenerateSegmentLine(S_OPEN_2));
		segment.push_back(GenerateSegmentLine(S_OPEN_3));
		segment.push_back(GenerateSegmentLine(S_OPEN_4));
		segment.push_back(GenerateSegmentLine(S_OPEN_5));
		segment.push_back(GenerateSegmentLine(S_OPEN_6));
		segment.push_back(GenerateSegmentLine(S_OPEN_7));
		break;

	case S_BIF:
		segment.push_back(GenerateSegmentLine(S_BIF_1));
		segment.push_back(GenerateSegmentLine(S_BIF_2));
		segment.push_back(GenerateSegmentLine(S_BIF_3));
		segment.push_back(GenerateSegmentLine(S_BIF_4));
		segment.push_back(GenerateSegmentLine(S_BIF_5));
		segment.push_back(GenerateSegmentLine(S_BIF_6));
		break;
	case S_BIF_R:
		segment.push_back(GenerateSegmentLine(S_BIF_R_1));
		segment.push_back(GenerateSegmentLine(S_BIF_R_2));
		segment.push_back(GenerateSegmentLine(S_BIF_R_3));
		segment.push_back(GenerateSegmentLine(S_BIF_R_4));
		segment.push_back(GenerateSegmentLine(S_BIF_R_5));
		segment.push_back(GenerateSegmentLine(S_BIF_R_6));
		break;

	case S_PRE_2_BR:
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_2));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_3));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_4));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_5));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_6));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_7));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_8));
		segment.push_back(GenerateSegmentLine(S_PRE_2_BR_9));
		break;
	case S_2_BR:
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_2_BR_1));
		break;
	case S_POST_2_BR:
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_1));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_2));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_3));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_4));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_5));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_6));
		segment.push_back(GenerateSegmentLine(S_POST_2_BR_7));
		break;

	case S_PRE_BR:
		segment.push_back(GenerateSegmentLine(S_PRE_BR_1));
		break;
	case S_BR:
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		segment.push_back(GenerateSegmentLine(S_BR_1));
		break;
	case S_POST_BR:
		segment.push_back(GenerateSegmentLine(S_POST_BR_1));
		break;

	case S_PRE_BR_L:
		segment.push_back(GenerateSegmentLine(S_PRE_BR_L_1));
		break;
	case S_BR_L:
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		segment.push_back(GenerateSegmentLine(S_BR_L_1));
		break;
	case S_POST_BR_L:
		segment.push_back(GenerateSegmentLine(S_POST_BR_L_1));
		break;

	case S_PRE_BR_R:
		segment.push_back(GenerateSegmentLine(S_PRE_BR_R_1));
		break;
	case S_BR_R:
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		segment.push_back(GenerateSegmentLine(S_BR_R_1));
		break;
	case S_POST_BR_R:
		segment.push_back(GenerateSegmentLine(S_POST_BR_R_1));
		break;

	case S_END:
		segment.push_back(GenerateSegmentLine(S_END_1));
		segment.push_back(GenerateSegmentLine(S_END_2));
		segment.push_back(GenerateSegmentLine(S_END_3));
		segment.push_back(GenerateSegmentLine(S_END_4));
		segment.push_back(GenerateSegmentLine(S_END_5));
		segment.push_back(GenerateSegmentLine(S_END_6));
		segment.push_back(GenerateSegmentLine(S_END_7));
		segment.push_back(GenerateSegmentLine(S_END_8));
		segment.push_back(GenerateSegmentLine(S_END_9));
		segment.push_back(GenerateSegmentLine(S_END_10));
		segment.push_back(GenerateSegmentLine(S_END_11));
		segment.push_back(GenerateSegmentLine(S_END_12));
		segment.push_back(GenerateSegmentLine(S_END_13));
		segment.push_back(GenerateSegmentLine(S_END_14));
		segment.push_back(GenerateSegmentLine(S_END_15));
		segment.push_back(GenerateSegmentLine(S_END_16));
		segment.push_back(GenerateSegmentLine(S_END_17));
		segment.push_back(GenerateSegmentLine(S_END_18));
		segment.push_back(GenerateSegmentLine(S_END_19));
		segment.push_back(GenerateSegmentLine(S_END_20));
		segment.push_back(GenerateSegmentLine(S_END_21));
		break;
	default:
		LOG("RoadSegment - Cannot generate segment %d\n", type);
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