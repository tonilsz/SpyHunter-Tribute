#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

using namespace std;

ModuleAudio::ModuleAudio( bool start_enabled) : Module( start_enabled)
{}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Start()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}
// Called before render is available
bool ModuleAudio::Resume()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}


	bullet = LoadFx("bullet.wav");
	copter = LoadFx("copter.wav");
	copter_bomb = LoadFx("copter_bomb.wav");
	explosion = LoadFx("explosion.wav");
	live_up = LoadFx("live_up.wav");
	pinchazo = LoadFx("pinchazo.wav");
	rocket = LoadFx("rocket.wav");
	spray = LoadFx("spray.wav");
	turn = LoadFx("turn.wav");

	return ret;
}

// Called before quitting
bool ModuleAudio::Stop()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	for (vector<Mix_Chunk*>::reverse_iterator it = fx.rbegin(); it != fx.rend(); ++it)
		Mix_FreeChunk(*it);

	fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if(music != nullptr)
	{
		if(fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int) (fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == nullptr)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(const char* path)
{
	unsigned int ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.push_back(chunk);
		ret = fx.size() - 1;
	}

	return ret;
}

// Play WAV
bool ModuleAudio::PlayFx(AUDIO_TYPE audio, int repeat)
{
	unsigned int id;
	bool ret = false;

	switch (audio){
	case 	AUD_BULLET:
		id =  bullet;
		break;

		case AUD_COPTER:
		id =  copter;
		break;

		case AUD_COPTER_BOMB:
		id =  copter_bomb;
		break;

		case AUD_EXPLOSION:
		id =  explosion;
		break;

		case AUD_LIVE_UP:
		id =  live_up;
		break;

		case AUD_PINCHAZO:
		id =  pinchazo;
		break;

		case AUD_ROCKET:
		id =  rocket;
		break;

		case AUD_SPRAY:
		id =  spray;
			break;

		case AUD_TURN:
		id =  turn;
			break;
	}
	if(id < fx.size())
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}



// Stop WAV
void ModuleAudio::StopFx()
{
	Mix_HaltChannel(-1);
}

