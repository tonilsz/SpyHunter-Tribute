#include "RoadSegment.h"
#include "Collider.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRoad.h"


//Generate specific Road Line
RoadLine* RoadSegment::GenerateSegmentLine(const LINE_TYPE &type){

	//generate tiles
	vector<SDL_Rect>* tiles = nullptr;
	switch (type){
	case  S_FAT_A_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A1, T_GRASS };
		break;
	case  S_FAT_A_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B1, T_GRASS };
		break;
	case  S_FAT_A_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_GRASS };
		break;
	case  S_FAT_A_4:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_GRASS };
		break;
	case  S_FAT_A_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A1, T_GRASS };
		break;
	case  S_FAT_A_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B1, T_GRASS };
		break;
	case  S_FAT_A_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_GRASS };
		break;
	case  S_FAT_A_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_GRASS };
		break;

	case  S_FAT_B_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_B2, T_GRASS };
		break;
	case  S_FAT_B_2:
		tiles = new vector<SDL_Rect>{ T_BUSH_B2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_A2, T_GRASS };
		break;
	case  S_FAT_B_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_TREE_A1 };
		break;
	case  S_FAT_B_4:
		tiles = new vector<SDL_Rect>{ T_BUSH_A1, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_GRASS };
		break;
	case  S_FAT_B_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_GRASS };
		break;
	case  S_FAT_B_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_BUSH_B2 };
		break;
	case  S_FAT_B_7:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_B1, T_GRASS };
		break;
	case  S_FAT_B_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_BUSH_B1 };
		break;

	case  S_THIN_A_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_BUSH_B1, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_BUSH_A2, T_GRASS, T_GRASS };
		break;
	case  S_THIN_A_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_BUSH_B2, T_GRASS, T_GRASS };
		break;
	case  S_THIN_A_3:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_BUSH_A2, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS, };
		break;
	case  S_THIN_A_4:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_B2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_THIN_A_5:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GRASS, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A1, T_GRASS, T_GRASS, T_TREE_A1 };
		break;
	case  S_THIN_A_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_BUSH_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_A2, T_GRASS, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_THIN_A_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_THIN_A_8:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GRASS, T_BUSH_A1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1 };
		break;

	case  S_THIN_B_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_BUSH_B2, T_GRASS, T_GRASS };
		break;
	case  S_THIN_B_2:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_BUSH_B1, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_B1 };
		break;
	case  S_THIN_B_3:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_A1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_THIN_B_4:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B1, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_THIN_B_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_BUSH_B2, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_B2, T_GRASS, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_THIN_B_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1 };
		break;
	case  S_THIN_B_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_GRASS, T_BUSH_A2, T_BUSH_B2 };
		break;
	case  S_THIN_B_8:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS };
		break;

	case  S_THIN_L_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_THIN_L_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_THIN_L_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_BUSH_B2, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_TREE_A1 };
		break;
	case  S_THIN_L_4:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_THIN_L_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_BUSH_A2, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS };
		break;
	case  S_THIN_L_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_THIN_L_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_GRASS, T_BUSH_A1, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1 };
		break;
	case  S_THIN_L_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS };
		break;

	case  S_THIN_R_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_BUSH_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS };
		break;
	case  S_THIN_R_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS };
		break;
	case  S_THIN_R_3:
		tiles = new vector<SDL_Rect>{ T_BUSH_B1, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS };
		break;
	case  S_THIN_R_4:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_A1, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS };
		break;
	case  S_THIN_R_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_BUSH_B1, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS };
		break;
	case  S_THIN_R_6:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_A1, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS };
		break;
	case  S_THIN_R_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_BUSH_A1, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS };
		break;
	case  S_THIN_R_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_A1, T_TREE_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS };
		break;

	case  S_2_ROADS_1:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_2_ROADS_2:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_2_ROADS_3:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_2_ROADS_4:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_2_ROADS_5:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A1, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_2_ROADS_6:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B2, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_2_ROADS_7:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_BUSH_A2, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_2_ROADS_8:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_BUSH_B1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;


	case  S_CUR_LC_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_LC_2:
		tiles = new vector<SDL_Rect>{ T_TREE_C2, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_D1, T_TREE_D2 };
		break;
	case  S_CUR_LC_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GCURR3_C1, T_RCURR3_C1, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_LC_4:
		tiles = new vector<SDL_Rect>{ T_TREE_E2, T_GRASS, T_GCURR3_B1, T_RCURR3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_B2, T_GCURR2_B2, T_GRASS, T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS };
		break;
	case  S_CUR_LC_5:
		tiles = new vector<SDL_Rect>{ T_TREE_D1, T_TREE_D2, T_GRASS, T_RCURR3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_A2, T_GCURR2_A2, T_GRASS, T_TREE_D1, T_TREE_D2, T_GRASS, T_GRASS };
		break;
	case  S_CUR_LC_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GRASS, T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2 };
		break;
	case  S_CUR_LC_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_B1, T_TREE_B2, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_LC_8:
		tiles = new vector<SDL_Rect>{ T_TREE_B2, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_TREE_D1, T_TREE_D2, T_TREE_D2, T_GRASS };
		break;
	case  S_CUR_CR_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GRASS, T_GRASS, T_TREE_C1, T_TREE_C2 };
		break;
	case  S_CUR_CR_2:
		tiles = new vector<SDL_Rect>{ T_TREE_E2, T_GRASS, T_GRASS, T_GRASS, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS, T_TREE_C1, T_TREE_C2 };
		break;
	case  S_CUR_CR_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GCURR3_C1, T_RCURR3_C1, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CR_4:
		tiles = new vector<SDL_Rect>{ T_TREE_B1, T_TREE_B2, T_GRASS, T_GRASS, T_GRASS, T_GCURR3_B1, T_RCURR3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_B2, T_GCURR2_B2, T_TREE_D1, T_TREE_D2 };
		break;
	case  S_CUR_CR_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2, T_TREE_E1, T_GRASS, T_RCURR3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_A2, T_GCURR2_A2, T_GRASS, T_TREE_D1 };
		break;
	case  S_CUR_CR_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_TREE_B1, T_TREE_B2, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CR_7:
		tiles = new vector<SDL_Rect>{ T_TREE_D1, T_TREE_D2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_TREE_B1 };
		break;
	case  S_CUR_CR_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_B1, T_TREE_B2, T_GRASS, T_TREE_B1, T_TREE_B2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_GRASS };
		break;
	case  S_CUR_RC_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_TREE_B1, T_TREE_B2, T_GRASS, T_GRASS, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_B2, T_GCURL2_B2, T_GRASS };
		break;
	case  S_CUR_RC_2:
		tiles = new vector<SDL_Rect>{ T_TREE_D1, T_TREE_E2, T_TREE_E2, T_GRASS, T_GRASS, T_GRASS, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_A2, T_GCURL2_A2, T_TREE_B1 };
		break;
	case  S_CUR_RC_3:
		tiles = new vector<SDL_Rect>{ T_TREE_E2, T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_C2, T_GCURL3_C2, T_GRASS, T_GRASS };
		break;
	case  S_CUR_RC_4:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_B1, T_TREE_B2, T_GRASS, T_GRASS, T_GCURL2_B1, T_RCURL2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_B2, T_GCURL3_B2, T_TREE_D1, T_TREE_D2 };
		break;
	case  S_CUR_RC_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS, T_GCURL2_A1, T_RCURL2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_A2, T_GRASS, T_GRASS, T_TREE_D1 };
		break;
	case  S_CUR_RC_6:
		tiles = new vector<SDL_Rect>{ T_TREE_B1, T_TREE_B2, T_GRASS, T_GRASS, T_GRASS, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_B2, T_GCURL2_B2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_RC_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_E1, T_TREE_E2, T_TREE_D2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_A2, T_GCURL2_A2, T_TREE_B1, T_TREE_B2, T_GRASS };
		break;
	case  S_CUR_RC_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_TREE_B1, T_TREE_B2, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_TREE_B1, T_TREE_B2 };
		break;
	case  S_CUR_CL_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_B2, T_GCURL2_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CL_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_D1, T_TREE_D2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_A2, T_GCURL2_A2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS };
		break;
	case  S_CUR_CL_3:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_C2, T_GCURL3_C2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_TREE_E1 };
		break;
	case  S_CUR_CL_4:
		tiles = new vector<SDL_Rect>{ T_TREE_B1, T_TREE_B2, T_GCURL2_B1, T_RCURL2_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_B2, T_GCURL3_B2, T_GRASS, T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2 };
		break;
	case  S_CUR_CL_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GCURL2_A1, T_RCURL2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_A2, T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CL_6:
		tiles = new vector<SDL_Rect>{ T_TREE_E2, T_GRASS, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_B2, T_GCURL2_B2, T_GRASS, T_GRASS, T_TREE_B1, T_TREE_B2, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CL_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL2_A2, T_GCURL2_A2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GRASS, T_GRASS };
		break;
	case  S_CUR_CL_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_D1, T_TREE_D2 };
		break;
	case  S_CLOSE_1:
		tiles = new vector<SDL_Rect>{ T_BUSH_A2, T_GRASS, T_GMINUS_G1, T_RMINUS_G1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_G2, T_GMINUS_G2, T_GRASS, T_GRASS };
		break;
	case  S_CLOSE_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B2, T_GMINUS_F1, T_RMINUS_F1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_F2, T_GMINUS_F2, T_GRASS, T_TREE_A1 };
		break;
	case  S_CLOSE_3:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GMINUS_E1, T_RMINUS_E1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_E2, T_GMINUS_E2, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_CLOSE_4:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GMINUS_D1, T_RMINUS_D1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_D2, T_GMINUS_D2, T_BUSH_A2, T_GRASS };
		break;
	case  S_CLOSE_5:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GMINUS_C1, T_RMINUS_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_C2, T_GMINUS_C2, T_BUSH_A1, T_BUSH_B1 };
		break;
	case  S_CLOSE_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GMINUS_B1, T_RMINUS_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_B2, T_GMINUS_B2, T_GRASS, T_BUSH_B1 };
		break;
	case  S_CLOSE_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A2, T_BUSH_B2, T_RMINUS_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_A2, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_CLOSE_8:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_BUSH_A1, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_TREE_A1 };
		break;
	case  S_CLOSE_9:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GMINUS_G1, T_RMINUS_G1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_G2, T_GMINUS_G2, T_BUSH_B2, T_GRASS, T_GRASS };
		break;
	case  S_CLOSE_10:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GMINUS_F1, T_RMINUS_F1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_F2, T_GMINUS_F2, T_BUSH_A2, T_GRASS, T_GRASS };
		break;
	case  S_CLOSE_11:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_GMINUS_E1, T_RMINUS_E1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_E2, T_GMINUS_E2, T_GRASS, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_CLOSE_12:
		tiles = new vector<SDL_Rect>{ T_BUSH_A1, T_GRASS, T_GRASS, T_GMINUS_D1, T_RMINUS_D1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_D2, T_GMINUS_D2, T_GRASS, T_BUSH_B1, T_TREE_A1 }	;
		break;
	case  S_CLOSE_13:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_B1, T_BUSH_A2, T_GMINUS_C1, T_RMINUS_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_C2, T_GMINUS_C2, T_BUSH_B1, T_BUSH_A1, T_GRASS };
		break;
	case  S_CLOSE_14:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GMINUS_B1, T_RMINUS_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_B2, T_GMINUS_B2, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_CLOSE_15:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GRASS, T_BUSH_A1, T_RMINUS_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_A2, T_TREE_A1, T_TREE_A2, T_GRASS, T_TREE_A1 };
		break;

	case  S_OPEN_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GCURL3_C1, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GCURR3_C2, T_GRASS, T_BUSH_B2, T_GRASS };
		break;
	case  S_OPEN_2:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_TREE_A1, T_TREE_A2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_BUSH_A2, T_GRASS, T_GRASS };
		break;
	case  S_OPEN_3:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GRASS, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_TREE_A1, T_TREE_A2, T_GRASS };
		break;
	case  S_OPEN_4:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_BUSH_A1, T_GRASS };
		break;
	case  S_OPEN_5:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GCURL3_C1, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GCURR3_C2, T_GRASS, T_TREE_A1 };
		break;
	case  S_OPEN_6:
		tiles = new vector<SDL_Rect>{ T_TREE_A1, T_TREE_A2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_TREE_A1, T_TREE_A2 };
		break;
	case  S_OPEN_7:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_BUSH_A1, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_GRASS, T_TREE_A1 };
		break;

	case  S_BIF_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GCURL3_C1, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GCURR3_C2, T_BUSH_B1 };
		break;
	case  S_BIF_2:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS };
		break;
	case  S_BIF_3:
		tiles = new vector<SDL_Rect>{ T_BUSH_A1, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_TREE_A1 };
		break;
	case  S_BIF_4:
		tiles = new vector<SDL_Rect>{ T_GCURL3_C1, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_C1, T_BIF_C, T_BIF_C2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GCURR3_C2 };
		break;
	case  S_BIF_5:
		tiles = new vector<SDL_Rect>{ T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_B1, T_BIF_B, T_BIF_B2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2 };
		break;
	case  S_BIF_6:
		tiles = new vector<SDL_Rect>{ T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_A1, T_BIF_A, T_BIF_A2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2 };
		break;
	case  S_BIF_R_1:
		tiles = new vector<SDL_Rect>{ T_GCURR3_C1, T_RCURR3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_D1, T_BIF_D, T_BIF_D2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_C2, T_GCURL3_C2 };
		break;
	case  S_BIF_R_2:
		tiles = new vector<SDL_Rect>{ T_GCURR3_B1, T_RCURR3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_E1, T_BIF_E, T_BIF_E2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_B2, T_GCURL3_B2 };
		break;
	case  S_BIF_R_3:
		tiles = new vector<SDL_Rect>{ T_GCURR3_A1, T_RCURR3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BIF_F1, T_BIF_F, T_BIF_F2, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_A2, T_GCURL3_A2 };
		break;
	case  S_BIF_R_4:
		tiles = new vector<SDL_Rect>{ T_BUSH_A2, T_GCURR3_C1, T_RCURR3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_C2, T_GCURL3_C2, T_TREE_A1 };
		break;
	case  S_BIF_R_5:
		tiles = new vector<SDL_Rect>{ T_TREE_A2, T_GCURR3_B1, T_RCURR3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_B2, T_GCURL3_B2, T_GRASS };
		break;
	case  S_BIF_R_6:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_GCURR3_A1, T_RCURR3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURL3_A2, T_GCURL3_A2, T_BUSH_B1 };
		break;

	case  S_PRE_2_BR_1:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_G2, T_GMINUS_G2, T_BUSH_A1, T_GMINUS_G1, T_RMINUS_G1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_PRE_2_BR_2:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_F2, T_GMINUS_F2, T_BUSH_A2, T_GMINUS_F1, T_RMINUS_F1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_PRE_2_BR_3:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_E2, T_GMINUS_E2, T_BUSH_B2, T_GMINUS_E1, T_RMINUS_E1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_PRE_2_BR_4:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_D2, T_GMINUS_D2, T_BUSH_A1, T_GMINUS_D1, T_RMINUS_D1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_PRE_2_BR_5:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_C2, T_GMINUS_C2, T_BUSH_B1, T_GMINUS_C1, T_RMINUS_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_PRE_2_BR_6:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_B2, T_GMINUS_B2, T_BUSH_A2, T_GMINUS_B1, T_RMINUS_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_PRE_2_BR_7:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RMINUS_A2, T_BUSH_B2, T_GRASS, T_BUSH_B1, T_RMINUS_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_PRE_2_BR_8:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_PRE_2_BR_9:
		tiles = new vector<SDL_Rect>{ T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_B2, T_WATER_TRANS_B2, T_RAIL_B1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2 };
		break;

	case  S_2_BR_1:	
		tiles = new vector<SDL_Rect>{ T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_A2, T_WATER, T_RAIL_A1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2 };
		break;


	case  S_POST_2_BR_1:
		tiles = new vector<SDL_Rect>{ T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_C2, T_WATER_TRANS_A2, T_RAIL_C1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2 };
		break;
	case  S_POST_2_BR_2:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_POST_2_BR_3:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2, T_GRASS, T_BUSH_A2, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_POST_2_BR_4:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2, T_GRASS, T_BUSH_B1, T_GRASS, T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_POST_2_BR_5:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_C2, T_GCURR3_C2, T_BUSH_A1, T_GCURL3_C1, T_RCURL3_C1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;
	case  S_POST_2_BR_6:
		tiles = new vector<SDL_Rect>{ T_RECT_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_BUSH_B2, T_GCURL3_B1, T_RCURL3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_B2 };
		break;
	case  S_POST_2_BR_7:
		tiles = new vector<SDL_Rect>{ T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_BUSH_A2, T_GCURL3_A1, T_RCURL3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RECT_A2 };
		break;

	case  S_PRE_BR_1:
		tiles = new vector<SDL_Rect>{ T_WATER_TRANS_B2, T_WATER_TRANS_B3, T_WATER_TRANS_B4, T_RAIL_B1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_B2, T_WATER_TRANS_B1, T_WATER_TRANS_B2, T_WATER_TRANS_B3 };
		break;
	case  S_BR_1:
		tiles = new vector<SDL_Rect>{ T_WATER, T_WATER, T_WATER, T_RAIL_A1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_A2, T_WATER, T_WATER, T_WATER };
		break;
	case  S_POST_BR_1:
		tiles = new  vector<SDL_Rect>{ T_WATER_TRANS_A2, T_WATER_TRANS_A3, T_WATER_TRANS_A4, T_RAIL_C1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_C2, T_WATER_TRANS_A1, T_WATER_TRANS_A2, T_WATER_TRANS_A3 };
		break;
	case  S_PRE_BR_L_1:
		tiles = new vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_B2, T_WATER_TRANS_B2, T_WATER_TRANS_B3, T_WATER_TRANS_B4, T_WATER_TRANS_B1, T_WATER_TRANS_B2, T_WATER_TRANS_B3 };
		break;
	case  S_BR_L_1:
		tiles = new  vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_A2, T_WATER, T_WATER, T_WATER, T_WATER, T_WATER, T_WATER };
		break;
	case  S_POST_BR_L_1:
		tiles = new  vector<SDL_Rect>{ T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_C2, T_WATER_TRANS_A2, T_WATER_TRANS_A3, T_WATER_TRANS_A4, T_WATER_TRANS_A1, T_WATER_TRANS_A2, T_WATER_TRANS_A3 };
		break;
	case  S_PRE_BR_R_1:
		tiles = new vector<SDL_Rect>{ T_WATER_TRANS_B2, T_WATER_TRANS_B3, T_WATER_TRANS_B4, T_WATER_TRANS_B1, T_WATER_TRANS_B2, T_WATER_TRANS_B3, T_RAIL_B1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_B2 };
		break;
	case  S_BR_R_1:
		tiles = new vector<SDL_Rect>{ T_WATER, T_WATER, T_WATER, T_WATER, T_WATER, T_WATER, T_RAIL_A1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_A2 };
		break;
	case  S_POST_BR_R_1:
		tiles = new vector<SDL_Rect>{ T_WATER_TRANS_A2, T_WATER_TRANS_A3, T_WATER_TRANS_A4, T_WATER_TRANS_A1, T_WATER_TRANS_A2, T_WATER_TRANS_A3, T_RAIL_C1, T_BRIDGE_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_BRIDGE_A2, T_RAIL_C2 };
		break;
		
		/* S_END_1, S_END_2, S_END_3, S_END_4, S_END_5, S_END_6, S_END_7, S_END_8, S_END_9, S_END_10, S_END_11, S_END_12, S_END_13, S_END_14, S_END_15, S_END_16, S_END_17, S_END_18, S_END_19, S_END_20, S_END_21,
		
		case  S_BR_1:
		tiles = new;
		break;
		*/
	default:
		LOG("RoadSegmentDefinition - Cannot generate line %d\n", type);
	}

	//generate colliders
	vector<Collider*>* mask = nullptr; 
	vector<Collider*>* right_mask = nullptr;
	switch (type){
	case  S_FAT_A_1: case  S_FAT_A_2: case  S_FAT_A_3: case  S_FAT_A_4: case  S_FAT_A_5: case  S_FAT_A_6: case  S_FAT_A_7: case  S_FAT_A_8:
	case  S_FAT_B_1: case  S_FAT_B_2: case  S_FAT_B_3: case  S_FAT_B_4: case  S_FAT_B_5: case  S_FAT_B_6: case  S_FAT_B_7: case  S_FAT_B_8:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 1, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 2, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 12, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 13, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_THIN_A_1: case  S_THIN_A_2: case  S_THIN_A_3: case  S_THIN_A_4: case  S_THIN_A_5: case  S_THIN_A_6: case  S_THIN_A_7: case  S_THIN_A_8:
	case  S_THIN_B_1: case  S_THIN_B_2: case  S_THIN_B_3: case  S_THIN_B_4: case  S_THIN_B_5: case  S_THIN_B_6: case  S_THIN_B_7: case  S_THIN_B_8:
	case  S_PRE_BR_1: case  S_BR_1: case  S_POST_BR_1:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 4, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 10, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_THIN_L_1: case  S_THIN_L_2: case  S_THIN_L_3: case  S_THIN_L_4: case  S_THIN_L_5: case  S_THIN_L_6: case  S_THIN_L_7: case  S_THIN_L_8:
	case  S_PRE_BR_L_1: case  S_BR_L_1: case  S_POST_BR_L_1:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 1, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_THIN_R_1: case  S_THIN_R_2: case  S_THIN_R_3: case  S_THIN_R_4: case  S_THIN_R_5: case  S_THIN_R_6: case  S_THIN_R_7: case  S_THIN_R_8:
	case  S_PRE_BR_R_1: case  S_BR_R_1: case  S_POST_BR_R_1:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 13, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_2_ROADS_1: case  S_2_ROADS_2: case  S_2_ROADS_3: case  S_2_ROADS_4: case  S_2_ROADS_5: case  S_2_ROADS_6: case  S_2_ROADS_7: case  S_2_ROADS_8:
	case  S_PRE_2_BR_1: case  S_PRE_2_BR_2: case  S_PRE_2_BR_3: case  S_PRE_2_BR_4: 
		mask = new vector<Collider*>{
			new Collider({ 2, RTILE_HEIGHT, 2, 0 }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_2_BR_1: case  S_PRE_2_BR_8: case  S_PRE_2_BR_9: case  S_POST_2_BR_1: case  S_POST_2_BR_2: case  S_POST_2_BR_3: case  S_POST_2_BR_4:
		mask = new vector<Collider*>{
			new Collider({ 2, RTILE_HEIGHT, 2, 0 }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 5, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 9, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;

	case  S_POST_2_BR_5:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 1, 4, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 3, 8, 1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_POST_2_BR_6:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 2, 4, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 2, 8, 1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_POST_2_BR_7:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 3, 4, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 1, 8, 1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_PRE_2_BR_5:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 3, 5, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 1, 7, -1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_PRE_2_BR_6:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 2, 5, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 2, 7, -1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_PRE_2_BR_7:
		mask = new vector<Collider*>{
			new Collider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		right_mask = GenerateCurveColliders(3, 1, 5, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(3, 3, 7, -1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;


	case  S_CLOSE_15:
		right_mask = GenerateCurveColliders(7, 1, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 1, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_14:
		right_mask = GenerateCurveColliders(7, 2, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 2, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_13:
		right_mask = GenerateCurveColliders(7, 3, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 3, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_12:
		right_mask = GenerateCurveColliders(7, 4, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 4, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_11:
		right_mask = GenerateCurveColliders(7, 5, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 5, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_10:
		right_mask = GenerateCurveColliders(7, 6, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 6, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_9:
		right_mask = GenerateCurveColliders(7, 7, 3, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 7, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_8:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 2, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 12, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_CLOSE_7:
		right_mask = GenerateCurveColliders(7, 1, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 1, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_6:
		right_mask = GenerateCurveColliders(7, 2, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 2, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_5:
		right_mask = GenerateCurveColliders(7, 3, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 3, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_4:
		right_mask = GenerateCurveColliders(7, 4, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 4, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_3:
		right_mask = GenerateCurveColliders(7, 5, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 5, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_2:
		right_mask = GenerateCurveColliders(7, 6, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 6, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CLOSE_1:
		right_mask = GenerateCurveColliders(7, 7, 2, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(7, 7, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_CUR_CL_8:
		mask = GenerateCurveColliders(3, 1, 1, 1, COL_ROAD_OUT);
		mask->push_back(new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		mask->push_back(new Collider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road));
		break;
	case  S_CUR_CL_7:
		right_mask = GenerateCurveColliders(3, 2, 1, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 1, 7, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_6:
		right_mask = GenerateCurveColliders(3, 3, 1, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 2, 7, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_5:
		right_mask = GenerateCurveColliders(2, 1, 2, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 8, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_4:
		right_mask = GenerateCurveColliders(2, 2, 2, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 8, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_3:
		right_mask = GenerateCurveColliders(3, 1, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 8, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_2:
		right_mask = GenerateCurveColliders(3, 2, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 1, 9, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CL_1:
		right_mask = GenerateCurveColliders(3, 3, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 2, 9, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;


	case  S_CUR_RC_8:
		mask = GenerateCurveColliders(3, 1, 4, 1, COL_ROAD_OUT);
		mask->push_back(new Collider({ RTILE_WIDTH * 10, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		mask->push_back(new Collider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road));
		break;
	case  S_CUR_RC_7:
		right_mask = GenerateCurveColliders(3, 2, 4, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 1, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_6:
		right_mask = GenerateCurveColliders(3, 3, 4, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 2, 10, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_5:
		right_mask = GenerateCurveColliders(2, 1, 5, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_4:
		right_mask = GenerateCurveColliders(2, 2, 5, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_3:
		right_mask = GenerateCurveColliders(3, 1, 6, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 11, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_2:
		right_mask = GenerateCurveColliders(3, 2, 6, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 1, 12, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_RC_1:
		right_mask = GenerateCurveColliders(3, 3, 6, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(2, 2, 12, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_CUR_LC_8:
		mask = GenerateCurveColliders(3, 3, 8, -1, COL_ROAD_BORDER);
		mask->push_back(new Collider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road));
		mask->push_back(new Collider({ RTILE_WIDTH * 4, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		break;
	case  S_CUR_LC_7:
		mask = GenerateCurveColliders(2, 1, 3, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 2, 8, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_6:
		mask = GenerateCurveColliders(2, 2, 3, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 1, 8, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_5:
		mask = GenerateCurveColliders(3, 3, 1, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(2, 1, 8, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_4:
		mask = GenerateCurveColliders(3, 2, 1, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(2, 2, 8, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_3:
		mask = GenerateCurveColliders(3, 1, 1, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 3, 6, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_2:
		mask = GenerateCurveColliders(2, 1, 1, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 2, 6, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_LC_1:
		mask = GenerateCurveColliders(2, 2, 1, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 1, 6, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_CUR_CR_8:
		mask = GenerateCurveColliders(3, 3, 11, -1, COL_ROAD_BORDER);
		mask->push_back(new Collider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road));
		mask->push_back(new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		break;
	case  S_CUR_CR_7:
		mask = GenerateCurveColliders(2, 1, 6, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 2, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_6:
		mask = GenerateCurveColliders(2, 2, 6, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 1, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_5:
		mask = GenerateCurveColliders(3, 3, 4, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(2, 1, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_4:
		mask = GenerateCurveColliders(3, 2, 4, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(2, 2, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_3:
		mask = GenerateCurveColliders(3, 1, 4, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 3, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_2:
		mask = GenerateCurveColliders(2, 1, 4, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 2, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_CUR_CR_1:
		mask = GenerateCurveColliders(2, 2, 4, -1, COL_ROAD_OUT);
		right_mask = GenerateCurveColliders(3, 1, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_OPEN_7:
		right_mask = GenerateCurveColliders(3, 1, 2, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 10, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_OPEN_6:
		right_mask = GenerateCurveColliders(3, 2, 2, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 10, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_OPEN_5:
		right_mask = GenerateCurveColliders(3, 3, 2, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 10, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_OPEN_4:
		mask = new vector<Collider*>{
			new Collider({ RTILE_WIDTH * 2, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),
			new Collider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),
			new Collider({ RTILE_WIDTH * 12, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) };
		break;
	case  S_OPEN_3:
		right_mask = GenerateCurveColliders(3, 1, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_OPEN_2:
		right_mask = GenerateCurveColliders(3, 2, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_OPEN_1:
		right_mask = GenerateCurveColliders(3, 3, 3, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 9, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_BIF_6:
		right_mask = GenerateCurveColliders(3, 1, 0, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 12, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		mask->push_back(new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		right_mask = GenerateCurveColliders(2, 1, 6, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(2, 1, 7, -1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_5:
		right_mask = GenerateCurveColliders(3, 2, 0, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 12, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		mask->push_back(new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road));
		right_mask = GenerateCurveColliders(2, 2, 6, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		right_mask = GenerateCurveColliders(2, 2, 7, -1, COL_ROAD_OUT);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_4:
		right_mask = GenerateCurveColliders(3, 3, 0, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 12, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_3:
		right_mask = GenerateCurveColliders(3, 1, 1, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_2:
		right_mask = GenerateCurveColliders(3, 2, 1, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_1:
		right_mask = GenerateCurveColliders(3, 3, 1, 1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 11, -1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;

	case  S_BIF_R_6:
		right_mask = GenerateCurveColliders(3, 3, 0, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 12, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_R_5:
		right_mask = GenerateCurveColliders(3, 2, 0, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 12, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_R_4:
		right_mask = GenerateCurveColliders(3, 1, 0, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 12, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_R_3:
		right_mask = GenerateCurveColliders(3, 3, -1, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 1, 13, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_R_2:
		right_mask = GenerateCurveColliders(3, 2, -1, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 2, 13, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		break;
	case  S_BIF_R_1:
		right_mask = GenerateCurveColliders(3, 1, -1, -1, COL_ROAD_OUT);
		mask = GenerateCurveColliders(3, 3, 13, 1, COL_ROAD_BORDER);
		mask->insert(mask->end(), right_mask->begin(), right_mask->end());
		mask->push_back(new Collider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road));
		break;

		/*
		case  S_END_1:
			tiles = new;
			break;
		S_END_1, S_END_2, S_END_3, S_END_4, S_END_5, S_END_6, S_END_7, S_END_8, S_END_9, S_END_10, S_END_11, S_END_12, S_END_13, S_END_14, S_END_15, S_END_16, S_END_17, S_END_18, S_END_19, S_END_20, S_END_21,
		*/
	default:
		LOG("RoadSegmentDefinition - Cannot generate line collider \n");
	}

	//generate new line
	RoadLine* res = new RoadLine(tiles, mask);
	return res;
}

//Generate Grup colliders for a road line
vector<Collider*>* RoadSegment::GenerateCurveColliders(const int &height, const int &piece, const int &pos, const int &dir, const COLLIDER_TYPE &collider_left){
	
	vector<Collider*>* res = nullptr;

	COLLIDER_TYPE collider_right;
	if (collider_left == COL_ROAD_BORDER)
		collider_right = COL_ROAD_OUT;
	else
		collider_right = COL_ROAD_BORDER;

	int despl = 0;

	int start;
	if (dir > 0){
		start = 0;
	}else
		start = 30;

	if (height == 7){
		despl = 4 * dir * (piece - 1);
		if (piece == 1 || piece == 2 || piece == 4 || piece == 6 || piece == 7){
			if (piece == 4) despl += (2 * dir);
			if (piece == 6 || piece == 7) despl += (4 * dir);

			res = new vector<Collider*>{};
			for (int i = 0; i < 2; ++i)
				res->push_back(new Collider({ (RTILE_WIDTH * (pos)) + (start + despl) + (2 * dir* i), (RTILE_HEIGHT / 2) * i, 2, RTILE_HEIGHT / 2 }, collider_left, App->road));
			for (int i = 0; i < 2; ++i)
				res->push_back(new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (2 * dir* i), (RTILE_HEIGHT / 2) * i, 2, RTILE_HEIGHT / 2 }, collider_right, App->road));
		}
		else{
			if (piece == 5) despl += (2 * dir);
			res = new vector<Collider*>{
				new Collider({ RTILE_WIDTH * pos + (start + despl), 0, 2, 21 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (2 * dir), 21, 2, 22 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (4 * dir), 43, 2, 21 }, collider_left, App->road),

				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl), 0, 2, 21 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (2 * dir), 21, 2, 22 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (4 * dir), 43, 2, 21 }, collider_right, App->road)
			};
		}
	}

	if (height == 3){
			if (piece == 2) despl += 10;
			if (piece == 3) despl += 21;
			if (piece == 4) despl += 31;
			if (piece == 5) despl += 42;
			if (dir == -1) despl += 10;

			res = new vector<Collider*>{
				new Collider({ RTILE_WIDTH * pos + (start + despl), 0, 2, 13 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (2 * dir), 13, 2, 13 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (4 * dir), 26, 2, 12 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (6 * dir), 38, 2, 13 }, collider_left, App->road),
				new Collider({ RTILE_WIDTH * pos + (start + despl) + (8 * dir), 51, 2, 13 }, collider_left, App->road),

				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl), 0, 2, 13 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (2 * dir), 13, 2, 13 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (4 * dir), 26, 2, 12 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (6 * dir), 38, 2, 13 }, collider_right, App->road),
				new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (8 * dir), 51, 2, 13 }, collider_right, App->road),
			};
	}

	if (height == 2){
		despl = 16 * dir * (piece - 1);
		res = new vector<Collider*>{};
		for (int i = 0; i < 8; ++i)
			res->push_back(new Collider({ (RTILE_WIDTH * (pos)) + (start + despl) + (2 * dir* i), 8 * i, 2, 8 }, collider_left, App->road));
		for (int i = 0; i < 8; ++i)
			res->push_back(new Collider({ (RTILE_WIDTH * (pos + 1)) + (start + despl) + (2 * dir* i), 8 * i, 2, 8 }, collider_right, App->road));
	}
	
	return res;
}