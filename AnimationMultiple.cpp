#include "AnimationMultiple.h"

AnimationMultiple::AnimationMultiple() : multi_frames(), speed(1.0f), current_frame(0.0f)
{}

vector<SDL_Rect>& AnimationMultiple::GetCurrentMultiFrame()
{
	current_frame += speed;
	if (current_frame >= multi_frames.size())
		current_frame = 0.0f;
	return multi_frames[(int)current_frame];
}


vector<SDL_Rect>* AnimationMultiple::GetMultiFrame(int frame)
{
	int size = multi_frames.size();
	if (frame > size)
		frame = 0;
	return size != 0 ? &multi_frames[frame] : NULL;
}

void AnimationMultiple::SetMultiFrame(int frame)
{
	if (frame > multi_frames.size())
		frame = 0;
	current_frame = frame;
}