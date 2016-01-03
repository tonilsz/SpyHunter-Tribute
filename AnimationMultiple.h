#ifndef __ANIMATION_MULTI_H__
#define __ANIMATION_MULTI_H__
#include <vector>

using namespace std;

class AnimationMultiple
{
public:
	float speed;
	vector<vector<SDL_Rect>> multi_frames;

private:
	float current_frame;

public:
	AnimationMultiple();

	vector<SDL_Rect>& GetCurrentMultiFrame();

	vector<SDL_Rect>* GetMultiFrame(int frame);

	void SetMultiFrame(int frame);
};
#endif // __ANIMATION_MULTI_H__