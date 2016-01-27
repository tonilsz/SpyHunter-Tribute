#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include <vector>
#include "Module.h"

enum AUDIO_TYPE {
	AUD_BULLET,
	AUD_COPTER,
	AUD_COPTER_BOMB,
	AUD_EXPLOSION,
	AUD_LIVE_UP,
	AUD_PINCHAZO,
	AUD_ROCKET,
	AUD_SPRAY,
	AUD_TURN
};

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();

	bool Start();
	bool Resume();
	bool Stop();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(AUDIO_TYPE audio, int repeat = 0);

	// Play a previously loaded WAV
	void StopFx();

	unsigned int bullet;
	unsigned int copter;
	unsigned int copter_bomb;
	unsigned int explosion;
	unsigned int live_up;
	unsigned int pinchazo;
	unsigned int rocket;
	unsigned int spray;
	unsigned int turn;

private:

	Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;
};

#endif // __MODULEAUDIO_H__