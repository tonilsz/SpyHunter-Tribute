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


#define S_CUR_LC_8 vector<SDL_Rect>{ T_TREE_B2, T_GRASS, T_GRASS, T_GRASS, T_RECT_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2 , T_TREE_D1 , T_TREE_D2 , T_TREE_D2, T_GRASS } 
#define S_CUR_LC_7 vector<SDL_Rect>{ T_GRASS, T_TREE_B1, T_TREE_B2, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS } 
#define S_CUR_LC_6 vector<SDL_Rect>{ T_GRASS, T_GRASS, T_GRASS, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_GCURR3_C2, T_RCURR3_C2, T_GRASS, T_GRASS, T_GRASS, T_TREE_E1, T_TREE_E2 } 
#define S_CUR_LC_5 vector<SDL_Rect>{ T_TREE_D1, T_TREE_D2, T_GCURR3_B1, T_RCURR3_B1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_B2, T_GCURR2_B2, T_GRASS, T_TREE_D1, T_TREE_D2, T_GRASS, T_GRASS }
#define S_CUR_LC_4 vector<SDL_Rect>{ T_TREE_E2, T_GRASS, T_GCURR3_A1, T_RCURR3_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR2_A2, T_GCURR2_A2, T_GRASS, T_GRASS, T_TREE_C1, T_TREE_C2,  T_GRASS } 
#define S_CUR_LC_3 vector<SDL_Rect>{ T_GRASS, T_GRASS, T_RCURR3_C1,T_GCURR3_C1, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_A2, T_GCURR3_A2, T_GRASS, T_GRASS, T_TREE_C1, T_TREE_C2, T_GRASS, T_GRASS, T_GRASS }
#define S_CUR_LC_2 vector<SDL_Rect>{ T_TREE_C2, T_GCURR2_A1, T_RCURR2_A1, T_ROAD, T_ROAD, T_ROAD, T_ROAD, T_RCURR3_B2, T_GCURR3_B2, T_GRASS, T_GRASS, T_GRASS, T_GRASS, T_TREE_D1, T_TREE_D2} 
#define S_CUR_LC_1 vector<SDL_Rect>{ T_GRASS, T_GCURR2_B1, T_RCURR2_B1, T_ROAD, T_ROAD, T_ROAD, T_GCURR3_C2, T_RCURR3_C2, T_GRASS, T_TREE_E1, T_TREE_E2, T_GRASS, T_GRASS, T_GRASS, T_GRASS} 


#define C_FAT vector<Collider*>{ new Collider({ RTILE_WIDTH * 1, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road),  new Collider({ RTILE_WIDTH * 2, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road),  new Collider({ RTILE_WIDTH * 12, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, App->road), new Collider({ RTILE_WIDTH * 13, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, App->road) }

#define C_THIN vector<Collider*>{ 
colliders.AddCollider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_THIN_L vector<Collider*>{ 
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 1, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_THIN_R vector<Collider*>{ 
colliders.AddCollider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 13, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_2_ROADS vector<Collider*>{ 
colliders.AddCollider({ 2, RTILE_HEIGHT, 2, 0 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_BRIDGE vector<Collider*>{ 
colliders.AddCollider({ RTILE_WIDTH * 3, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_BRIDGE_L vector<Collider*>{ 
colliders.AddCollider({ 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 1, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_BRIDGE_R vector<Collider*>{ 
colliders.AddCollider({ 0 * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 7, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 13, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_2_BRIDGES vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 14, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
#define C_POST_2_BRIDGES_1 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 8, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 6, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 4, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 2, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 8, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 6, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 4, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 2, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 22, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 24, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 26, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 28, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 30, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 22, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 24, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 26, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 28, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 30, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}
{11, 10, 11, 11, 10, 11}
#define C_POST_2_BRIDGES_2 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 20, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 18, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 16, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 14, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 12, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 10, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 20, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 18, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 16, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 14, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 12, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 10, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 10, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 12, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 14, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 16, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 18, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 20, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 10, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 12, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 14, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 16, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 18, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 20, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

{12, 13, 12, 13, 12}]
#define C_POST_2_BRIDGES_3 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 30, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 28, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 26, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 24, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 22, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 30, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 28, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 26, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 24, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 22, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8    , 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 2, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 4, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 6, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 8, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9    , 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 2, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 4, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 6, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 8, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}


#define C_PRE_2_BRIDGES_1 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 30, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 28, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 30, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 28, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 2, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 2, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

#define C_PRE_2_BRIDGES_2 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 26, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 24, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 26, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 24, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 4, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 6, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 4, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 6, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

#define C_PRE_2_BRIDGES_3 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 22, 0, 2, 21 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 20, 13, 2, 22 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 18, 13, 2, 21 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 22, 0, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 20, 13, 2, 22 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 18, 13, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 8, 0, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 10, 13, 2, 22 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 12, 13, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 +  8, 0, 2, 21 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 10, 13, 2, 22 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 12, 13, 2, 21 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

#define C_PRE_2_BRIDGES_4 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 16, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 14, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 16, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 14, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 14, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 16, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 14, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 16, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

#define C_PRE_2_BRIDGES_5 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 12, 0, 2, 21 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 10, 13, 2, 22 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 8, 13, 2, 21 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 12, 0, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 10, 13, 2, 22 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 8, 13, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 18, 0, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 20, 13, 2, 22 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 22, 13, 2, 21 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 18, 0, 2, 21 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 20, 13, 2, 22 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 22, 13, 2, 21 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}


#define C_PRE_2_BRIDGES_6 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 6, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 4, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 6, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 4, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 24, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 26, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 24, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 26, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

#define C_PRE_2_BRIDGES_7 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 2, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 2, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 28, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 30, RTILE_HEIGHT / 2, 2, RTILE_HEIGHT / 2 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 28, 0, 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 30, 13RTILE_HEIGHT / 2 2, RTILE_HEIGHT / 2 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}


#define C_OPEN_1 vector<Collider*>{ 
colliders.AddCollider({ RTILE_WIDTH * 3 + 30, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 3 + 28, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 3 + 26, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 3 + 24, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 3 + 22, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 4 + 30, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4 + 28, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4 + 26, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4 + 24, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 4 + 22, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 10 + 2, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10 + 4, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10 + 6, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10 + 8, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 10 + 10, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 11 + 2, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11 + 4, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11 + 6, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11 + 8, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 11 + 10, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

{11, 10, 11, 11, 10, 11}
#define C_OPEN_2 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 20, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 18, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 16, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 14, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 12, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 10, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 20, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 18, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 16, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 14, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 12, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 10, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8 + 10, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 12, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 14, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 16, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 18, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 20, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9 + 10, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 12, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 14, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 16, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 18, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 20, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}

{12, 13, 12, 13, 12}]
#define C_OPEN_3 vector<Collider*>{ 
colliders.AddCollider({ 0, 0, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 0, 0, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 5 + 30, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 28, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 26, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 24, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 5 + 22, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 6 + 30, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 28, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 26, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 24, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 6 + 22, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 8, 0, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 2, 13, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 4, 26, 2, 12 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 6, 38, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 8 + 8, 51, 2, 13 }, COL_ROAD_BORDER, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 9, 0, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 2, 13, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 4, 26, 2, 12 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 6, 38, 2, 13 }, COL_ROAD_OUT, ModuleRoad),
colliders.AddCollider({ RTILE_WIDTH * 9 + 8, 51, 2, 13 }, COL_ROAD_OUT, ModuleRoad),

colliders.AddCollider({ RTILE_WIDTH * 14, RTILE_HEIGHT, RTILE_WIDTH, RTILE_HEIGHT }, COL_ROAD_BORDER, ModuleRoad),
colliders.AddCollider({ (RTILE_WIDTH * 15) - 2, RTILE_HEIGHT, 2, RTILE_HEIGHT }, COL_ROAD_OUT, ModuleRoad)}


CUR 7
[{32, 32}{32, 32}{21, 22, 21}{32, 32}{21, 22, 21}{32, 32}{32, 32}]

CUR 3
[{13, 13, 12, 13, 13}{11, 10, 11, 11, 10, 11}{13, 13, 12, 13, 13}]

CUR 2
[{8, 8, 8, 8, 8, 8, 8, 8}{8, 8, 8, 8, 8, 8, 8, 8}]

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