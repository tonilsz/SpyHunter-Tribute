#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModulePlayer;
class ModuleRoad;
class ModuleDriver;
class ModuleCollision;
class ModuleParticles;

class Application
{
public:

	Application();
	~Application();

	bool Start();
	update_status Update();
	bool Stop();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleRoad* road;
	ModuleDriver* driver;
	ModuleCollision* masks;
	ModuleParticles* particles;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_H__