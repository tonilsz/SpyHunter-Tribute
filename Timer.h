#ifndef __TIMER_H__
#define __TIMER_H__
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "SDL_ttf/include/SDL_ttf.h"
#include <string>
#include <sstream>

using namespace std;

class Timer
{
public:
	bool quit = false;
	Uint32 start = 0;
	bool running = false;

private:
	float current_time;

public:
	Timer();

	void Start();

	void Stop();

	int GetTime();
};
#endif // __TIMER_H__