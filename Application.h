#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModulePlayer;
class ModuleCar;
class ModuleRoad;

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
	ModuleParticules* particules;
	ModuleCar* car;
	ModuleCollision* masks;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__