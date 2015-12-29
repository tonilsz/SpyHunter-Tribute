#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation();

	SDL_Rect& GetCurrentFrame();

	SDL_Rect& GetFrame(int frame);

	void SetFrame(int frame);
};