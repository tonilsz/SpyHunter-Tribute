#ifndef __ROADLINE_H__
#define __ROADLINE_H__
#include "Globals.h"
#include "Point.h"
#include "Collider.h"

#include <vector>

using namespace std;

// ::Road Tiles:: -------------
// Green Tiles -------------
#define T_GRASS SDL_Rect {0,0,32,64}
#define T_BUSH_A1 SDL_Rect {32,0,32,64}
#define T_BUSH_A2 SDL_Rect {64,0,32,64}
#define T_BUSH_B1 SDL_Rect {96,0,32,64}
#define T_BUSH_B2 SDL_Rect {128,0,32,64}
#define T_TREE_A1 SDL_Rect {160,0,32,64}
#define T_TREE_A2 SDL_Rect {192,0,32,64}
#define T_TREE_B1 SDL_Rect {224,0,32,64}
#define T_TREE_B2 SDL_Rect {256,0,32,64}
#define T_TREE_C1 SDL_Rect {288,0,32,64}
#define T_TREE_C2 SDL_Rect {320,0,32,64}
#define T_TREE_D1 SDL_Rect {352,0,32,64}
#define T_TREE_D2 SDL_Rect {384,0,32,64}
#define T_TREE_E1 SDL_Rect {416,0,32,64}
#define T_TREE_E2 SDL_Rect {448,0,32,64}
// Rect Tiles -------------
#define T_ROAD SDL_Rect {0,64,32,64}
#define T_SAND SDL_Rect {32,64,32,64}
#define T_RECT_A1 SDL_Rect {64,64,32,64}
#define T_RECT_A2 SDL_Rect {96,64,32,64}
#define T_RECT_B1 SDL_Rect {128,64,32,64}
#define T_RECT_B2 SDL_Rect {160,64,32,64}
// Road  Minus Tiles -------------
#define T_RMINUS_A1 SDL_Rect {0,128,32,64}
#define T_RMINUS_A2 SDL_Rect {32,128,32,64}
#define T_RMINUS_B1 SDL_Rect {64,128,32,64}
#define T_RMINUS_B2 SDL_Rect {96,128,32,64}
#define T_RMINUS_C1 SDL_Rect {128,128,32,64} 
#define T_RMINUS_C2 SDL_Rect {160,128,32,64}
#define T_RMINUS_D1 SDL_Rect {192,128,32,64}
#define T_RMINUS_D2 SDL_Rect {224,128,32,64}
#define T_RMINUS_E1 SDL_Rect {256,128,32,64}
#define T_RMINUS_E2 SDL_Rect {288,128,32,64}
#define T_RMINUS_F1 SDL_Rect {320,128,32,64}
#define T_RMINUS_F2 SDL_Rect {352,128,32,64}
#define T_RMINUS_G1 SDL_Rect {384,128,32,64}
#define T_RMINUS_G2 SDL_Rect {416,128,32,64}
// Grass Minus Tiles -------------
//#define T_GMINUS_A1 SDL_Rect {0,192,32,64}
//#define T_GMINUS_A2 SDL_Rect {32,192,32,64}
#define T_GMINUS_B1 SDL_Rect {64,192,32,64}
#define T_GMINUS_B2 SDL_Rect {96,192,32,64}
#define T_GMINUS_C1 SDL_Rect {128,192,32,64} 
#define T_GMINUS_C2 SDL_Rect {160,192,32,64}
#define T_GMINUS_D1 SDL_Rect {192,192,32,64}
#define T_GMINUS_D2 SDL_Rect {224,192,32,64}
#define T_GMINUS_E1 SDL_Rect {256,192,32,64}
#define T_GMINUS_E2 SDL_Rect {288,192,32,64}
#define T_GMINUS_F1 SDL_Rect {320,192,32,64}
#define T_GMINUS_F2 SDL_Rect {352,192,32,64}
#define T_GMINUS_G1 SDL_Rect {384,192,32,64}
#define T_GMINUS_G2 SDL_Rect {416,192,32,64}
// Curves Tiles (tiles horizontal x tiles vertical) ------------- 
// Road	Curve Left 2 x 1
#define T_RCURL2_A1 SDL_Rect {0,256,32,64}
#define T_RCURL2_A2 SDL_Rect {32,256,32,64}
#define T_RCURL2_B1 SDL_Rect {64,256,32,64}
#define T_RCURL2_B2 SDL_Rect {96,256,32,64}
// Road	Curve Right 2 x 1
#define T_RCURR2_A1 SDL_Rect {128,256,32,64}
#define T_RCURR2_A2 SDL_Rect {160,256,32,64}
#define T_RCURR2_B1 SDL_Rect {192,256,32,64}
#define T_RCURR2_B2 SDL_Rect {224,256,32,64}
// Road	Curve Right 3 x 1
#define T_RCURR3_A1 SDL_Rect {256,256,32,64}
#define T_RCURR3_A2 SDL_Rect {288,256,32,64}
#define T_RCURR3_B1 SDL_Rect {320,256,32,64}
#define T_RCURR3_B2 SDL_Rect {352,256,32,64}
#define T_RCURR3_C1 SDL_Rect {384,256,32,64}
#define T_RCURR3_C2 SDL_Rect {416,256,32,64}
// Road	Curve Left 3 x 1
#define T_RCURL3_A1 SDL_Rect {448,256,32,64}
#define T_RCURL3_A2 SDL_Rect {480,256,32,64}
#define T_RCURL3_B1 SDL_Rect {512,256,32,64}
#define T_RCURL3_B2 SDL_Rect {544,256,32,64}
#define T_RCURL3_C1 SDL_Rect {576,256,32,64}
#define T_RCURL3_C2 SDL_Rect {608,256,32,64}
// Grass Curve Left 2 x 1
#define T_GCURL2_A1 SDL_Rect {0,320,32,64}
#define T_GCURL2_A2 SDL_Rect {32,320,32,64}
#define T_GCURL2_B1 SDL_Rect {64,320,32,64}
#define T_GCURL2_B2 SDL_Rect {96,320,32,64}
// Grass Curve Right 2 x 1
#define T_GCURR2_A1 SDL_Rect {128,320,32,64}
#define T_GCURR2_A2 SDL_Rect {160,320,32,64}
#define T_GCURR2_B1 SDL_Rect {192,320,32,64}
#define T_GCURR2_B2 SDL_Rect {224,320,32,64}
// Grass Curve Right 3 x 1
#define T_GCURR3_A1 SDL_Rect {256,320,32,64}
#define T_GCURR3_A2 SDL_Rect {288,320,32,64}
#define T_GCURR3_B1 SDL_Rect {320,320,32,64}
#define T_GCURR3_B2 SDL_Rect {352,320,32,64}
#define T_GCURR3_C1 SDL_Rect {384,320,32,64}
#define T_GCURR3_C2 SDL_Rect {416,320,32,64}
// Grass Curve Left 3 x 1
#define T_GCURL3_A1 SDL_Rect {448,320,32,64}
#define T_GCURL3_A2 SDL_Rect {480,320,32,64}
#define T_GCURL3_B1 SDL_Rect {512,320,32,64}
#define T_GCURL3_B2 SDL_Rect {544,320,32,64}
#define T_GCURL3_C1 SDL_Rect {576,320,32,64}
#define T_GCURL3_C2 SDL_Rect {608,320,32,64}
// Escape Tiles to Rigth-------------
#define T_ESCR_END_A SDL_Rect {0,384,32,64}
#define T_ESCR_END_B1 SDL_Rect {32,384,32,64}
#define T_ESCR_END_B2 SDL_Rect {64,384,32,64}
#define T_ESCR_END_C1 SDL_Rect {96,384,32,64}
#define T_ESCR_END_C2 SDL_Rect {128,384,32,64}
#define T_ESCR_END_C3 SDL_Rect {160,384,32,64}
#define T_ESCR_CUR_A1 SDL_Rect {192,384,32,64}
#define T_ESCR_CUR_A2 SDL_Rect {224,384,32,64}
#define T_ESCR_CUR_A3 SDL_Rect {256,384,32,64}
#define T_ESCR_CUR_A4 SDL_Rect {288,384,32,64}
#define T_ESCR_CUR_B1 SDL_Rect {320,384,32,64}
#define T_ESCR_CUR_B2 SDL_Rect {352,384,32,64}
#define T_ESCR_CUR_B3 SDL_Rect {384,384,32,64}
#define T_ESCR_RECT_L SDL_Rect {416,384,32,64}
#define T_ESCR_RECT SDL_Rect {448,384,32,64}
#define T_ESCR_RECT_R SDL_Rect {480,384,32,64}
#define T_ESCR_START SDL_Rect {512,384,32,64}
// Escape Tiles to Left-------------
#define T_ESCL_END_A SDL_Rect {0,448,32,64}
#define T_ESCL_END_B1 SDL_Rect {32,448,32,64}
#define T_ESCL_END_B2 SDL_Rect {64,448,32,64}
#define T_ESCL_END_C1 SDL_Rect {96,448,32,64}
#define T_ESCL_END_C2 SDL_Rect {128,448,32,64}
#define T_ESCL_END_C3 SDL_Rect {160,448,32,64}
#define T_ESCL_CUR_A1 SDL_Rect {192,448,32,64}
#define T_ESCL_CUR_A2 SDL_Rect {224,448,32,64}
#define T_ESCL_CUR_A3 SDL_Rect {256,448,32,64}
#define T_ESCL_CUR_A4 SDL_Rect {288,448,32,64}
#define T_ESCL_CUR_B1 SDL_Rect {320,448,32,64}
#define T_ESCL_CUR_B2 SDL_Rect {352,448,32,64}
#define T_ESCL_CUR_B3 SDL_Rect {384,448,32,64}
#define T_ESCL_RECT_L SDL_Rect {416,448,32,64}
#define T_ESCL_RECT SDL_Rect {448,448,32,64}
#define T_ESCL_RECT_R SDL_Rect {480,448,32,64}
#define T_ESCL_START SDL_Rect {512,448,32,64}
// Water Tiles -------------
#define T_WATER SDL_Rect {0,512,32,64}
#define T_BRIDGE_A2 SDL_Rect {32,512,32,64}
#define T_BRIDGE_A1 SDL_Rect {64,512,32,64}
#define T_RAIL_A1 SDL_Rect {96,512,32,64}
#define T_RAIL_A2 SDL_Rect {128,512,32,64}
#define T_RAIL_B1 SDL_Rect {160,512,32,64}
#define T_RAIL_B2 SDL_Rect {192,512,32,64}
#define T_RAIL_C1 SDL_Rect {224,512,32,64}
#define T_RAIL_C2 SDL_Rect {256,512,32,64}
#define T_WATER_TRANS_A1 SDL_Rect {288,512,32,64}
#define T_WATER_TRANS_A2 SDL_Rect {320,512,32,64}
#define T_WATER_TRANS_A3 SDL_Rect {352,512,32,64}
#define T_WATER_TRANS_A4 SDL_Rect {384,512,32,64}
#define T_WATER_TRANS_B1 SDL_Rect {416,512,32,64}
#define T_WATER_TRANS_B2 SDL_Rect {448,512,32,64}
#define T_WATER_TRANS_B3 SDL_Rect {480,512,32,64}
#define T_WATER_TRANS_B4 SDL_Rect {512,512,32,64}
// Bifurcartion Tiles -------------
#define T_BIF_A1 SDL_Rect {0,576,32,64} 
#define T_BIF_A SDL_Rect {32,576,32,64}
#define T_BIF_A2 SDL_Rect {64,576,32,64}
#define T_BIF_B1 SDL_Rect {96,576,32,64} 
#define T_BIF_B SDL_Rect {128,576,32,64}
#define T_BIF_B2 SDL_Rect {160,576,32,64}
#define T_BIF_C1 SDL_Rect {192,576,32,64} 
#define T_BIF_C SDL_Rect {224,576,32,64}
#define T_BIF_C2 SDL_Rect {256,576,32,64}
#define T_BIF_D1 SDL_Rect {288,576,32,64} 
#define T_BIF_D SDL_Rect {320,576,32,64}
#define T_BIF_D2 SDL_Rect {352,576,32,64}
#define T_BIF_E1 SDL_Rect {384,576,32,64} 
#define T_BIF_E SDL_Rect {416,576,32,64}
#define T_BIF_E2 SDL_Rect {448,576,32,64}
#define T_BIF_F1 SDL_Rect {480,576,32,64} 
#define T_BIF_F SDL_Rect {512,576,32,64}
#define T_BIF_F2 SDL_Rect {544,576,32,64}

class RoadLine
{
public:
	vector<SDL_Rect>* line;
	vector<Collider*>* mask;
	int pos;

	RoadLine(vector<SDL_Rect>* line, vector<Collider*>* mask);

	~RoadLine();

	void SetTile(int pos, const SDL_Rect &tile);

	SDL_Rect* GetCourrentTile();

	void CleanLine();
};

#endif // __ROADLINE_H__