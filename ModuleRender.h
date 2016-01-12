#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

enum RENDER_TYPE{RENDER_PLAYER, RENDER_ROAD, RENDER_OTHER};

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool Stop();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, RENDER_TYPE type = RENDER_ROAD, int dist = 0);
	bool Shadow(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

public:
	bool printer_mode;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MODULERENDER_H__