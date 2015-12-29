#include "Timer.h"

Timer::Timer(){}

void Timer::Start(){
	running = true;
	start = SDL_GetTicks();
}

void Timer::Stop(){
	running = false;
	start = 0;
}

int Timer::GetTime(){
	return (int) SDL_GetTicks() - start;
}