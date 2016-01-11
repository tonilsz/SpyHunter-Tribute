/*#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

	Animation();

	SDL_Rect& GetCurrentFrame();

	SDL_Rect& GetFrame(int frame);

	void SetFrame(int frame);

private:
	float current_frame;
};
#endif // __ANIMATION_H__*/
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

using namespace std;

class Animation
{
public:
	float speed = 1.0f;
	bool loop = true;
	bool repeat = false;
	vector<SDL_Rect> frames;

private:
	float current_frame = 0.0f;
	int loops = 0;

public:
	Animation(bool repeat = true) : frames(), speed(1.0f), current_frame(0.0f), repeat(repeat)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.size())
		{
			current_frame = (loop) ? 0.0f : frames.size() - 1;
			loops++;
		}
		return frames[(int)current_frame];
	}

	const SDL_Rect& PeekCurrentFrame() const
	{
		return frames[(int)current_frame];
	}

	SDL_Rect& GetLastFrame() 	
	{
		return frames[(frames.size() - 1)];
	}

	SDL_Rect& GetFirstFrame()
	{
		return frames[0];
	}

	bool Finished()
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
	}
};

#endif // __ANIMATION_H__