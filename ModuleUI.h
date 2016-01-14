#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include<list>
#include "Module.h"
#include "Globals.h"

#include "SDL_ttf/include/SDL_ttf.h"

#define WHITE { 255, 255, 255 }
#define BLUE { 0, 0, 255 }

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	bool Resume();
	update_status Update();
	bool Stop();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

	SDL_Texture *score = NULL;
	SDL_Texture *lives = NULL;
	SDL_Texture *weapons = NULL;
	
	//The font that's going to be used
	TTF_Font *font = NULL;

	//The color of the font
	SDL_Color textColor;
};

#endif // __MODULEUI_H__