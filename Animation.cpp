#include "Animation.h"

	Animation::Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect& Animation::GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	SDL_Rect& Animation::GetFrame(int frame)
	{
		if (frame > frames.size())
			frame = 0;
		return frames[frame];
	}

	void Animation::SetFrame(int frame)
	{
		if (frame > frames.size())
			frame = 0;
		current_frame = frame;
	}