#ifndef __ROADSEGMENT_H__
#define __ROADSEGMENT_H__
#include "Globals.h"
#include "Point.h"
#include "RoadLine.h"

#include <vector>

using namespace std;

enum SEGMENT_TYPE
{
	S_FAT_A, S_FAT_B,
	S_THIN_A, S_THIN_B, S_THIN_L, S_THIN_R,
	S_CUR_LC, S_CUR_CR, S_CUR_RC, S_CUR_CL,
	S_OPEN, S_CLOSE, 
	S_BIF, S_2_ROADS, S_BIF_R, S_END,
	S_PRE_2_BR,	S_2_BR,	S_POST_2_BR,
	S_PRE_BR, S_BR, S_POST_BR,
	S_PRE_BR_L, S_BR_L, S_POST_BR_L,
	S_PRE_BR_R, S_BR_R, S_POST_BR_R,
};

enum LINE_TYPE
{
	S_FAT_A_1, S_FAT_A_2, S_FAT_A_3, S_FAT_A_4, S_FAT_A_5, S_FAT_A_6, S_FAT_A_7, S_FAT_A_8,
	S_FAT_B_1, S_FAT_B_2, S_FAT_B_3, S_FAT_B_4, S_FAT_B_5, S_FAT_B_6, S_FAT_B_7, S_FAT_B_8,
	S_THIN_A_1, S_THIN_A_2, S_THIN_A_3, S_THIN_A_4, S_THIN_A_5, S_THIN_A_6, S_THIN_A_7, S_THIN_A_8,
	S_THIN_B_1, S_THIN_B_2, S_THIN_B_3, S_THIN_B_4, S_THIN_B_5, S_THIN_B_6, S_THIN_B_7, S_THIN_B_8,
	S_THIN_L_1, S_THIN_L_2, S_THIN_L_3, S_THIN_L_4, S_THIN_L_5, S_THIN_L_6, S_THIN_L_7, S_THIN_L_8,
	S_THIN_R_1, S_THIN_R_2, S_THIN_R_3, S_THIN_R_4, S_THIN_R_5, S_THIN_R_6, S_THIN_R_7, S_THIN_R_8,
	S_2_ROADS_1, S_2_ROADS_2, S_2_ROADS_3, S_2_ROADS_4, S_2_ROADS_5, S_2_ROADS_6, S_2_ROADS_7, S_2_ROADS_8,
	S_CUR_LC_1, S_CUR_LC_2, S_CUR_LC_3, S_CUR_LC_4, S_CUR_LC_5, S_CUR_LC_6, S_CUR_LC_7, S_CUR_LC_8,
	S_CUR_CR_1, S_CUR_CR_2, S_CUR_CR_3, S_CUR_CR_4, S_CUR_CR_5, S_CUR_CR_6, S_CUR_CR_7, S_CUR_CR_8,
	S_CUR_RC_1, S_CUR_RC_2, S_CUR_RC_3, S_CUR_RC_4, S_CUR_RC_5, S_CUR_RC_6, S_CUR_RC_7, S_CUR_RC_8,
	S_CUR_CL_1, S_CUR_CL_2, S_CUR_CL_3, S_CUR_CL_4, S_CUR_CL_5, S_CUR_CL_6, S_CUR_CL_7, S_CUR_CL_8,
	S_CLOSE_1, S_CLOSE_2, S_CLOSE_3, S_CLOSE_4, S_CLOSE_5, S_CLOSE_6, S_CLOSE_7, S_CLOSE_8, S_CLOSE_9, S_CLOSE_10, S_CLOSE_11, S_CLOSE_12, S_CLOSE_13, S_CLOSE_14, S_CLOSE_15,
	S_OPEN_1, S_OPEN_2, S_OPEN_3, S_OPEN_4, S_OPEN_5, S_OPEN_6, S_OPEN_7,
	S_BIF_1, S_BIF_2, S_BIF_3, S_BIF_4, S_BIF_5, S_BIF_6,
	S_BIF_R_1, S_BIF_R_2, S_BIF_R_3, S_BIF_R_4, S_BIF_R_5, S_BIF_R_6,
	S_PRE_2_BR_1, S_PRE_2_BR_2, S_PRE_2_BR_3, S_PRE_2_BR_4, S_PRE_2_BR_5, S_PRE_2_BR_6, S_PRE_2_BR_7, S_PRE_2_BR_8, S_PRE_2_BR_9,
	S_2_BR_1,
	S_POST_2_BR_1, S_POST_2_BR_2, S_POST_2_BR_3, S_POST_2_BR_4, S_POST_2_BR_5, S_POST_2_BR_6, S_POST_2_BR_7,
	S_END_1, S_END_2, S_END_3, S_END_4, S_END_5, S_END_6, S_END_7, S_END_8, S_END_9, S_END_10, S_END_11, S_END_12, S_END_13, S_END_14, S_END_15, S_END_16, S_END_17, S_END_18, S_END_19, S_END_20, S_END_21,
	S_PRE_BR_1, S_BR_1, S_POST_BR_1,
	S_PRE_BR_L_1, S_BR_L_1, S_POST_BR_L_1,
	S_PRE_BR_R_1, S_BR_R_1, S_POST_BR_R_1,
};


	class RoadSegment
	{
	public:
		vector<RoadLine*> segment;
		int pos;
		SEGMENT_TYPE type;

		RoadSegment(const SEGMENT_TYPE &type);

		~RoadSegment();

		void AddRoadLine(RoadLine* line);

		RoadLine* GetCourrentLine();

		void GenerateSegment(const SEGMENT_TYPE &type);

		RoadLine* RoadSegment::GenerateSegment(const LINE_TYPE &type);
	
		int GetSize();

	private:
		void CleanSegment();

		vector<Collider*>* RoadSegment::GenerateCurveColliders(const int &height, const int &piece, const int &pos, const int &dir, const COLLIDER_TYPE &collider_left);
	};

#endif // __ROADSEGMENT_H__