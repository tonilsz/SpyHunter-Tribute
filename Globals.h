#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Configuration -----------
#define ROAD_TILE_WIDTH 32
#define ROAD_TILE_HEIGHT 64
#define STILE_WIDTH 32
#define STILE_HEIGHT 32
#define MTILE_WIDTH 64
#define MTILE_HEIGHT 64
#define LTILE_WIDTH 96
#define LTILE_HEIGHT 96
#define SCREEN_WIDTH 13 * ROAD_TILE_WIDTH
#define SCREEN_HEIGHT 7.5 * ROAD_TILE_HEIGHT
#define SCREEN_SIZE 1
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Spy Hunter"

#endif //__GLOBALS_H__