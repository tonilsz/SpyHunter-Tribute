#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModulePlayer.h"
#include "ModuleRoad.h"
#include "SDL/include/SDL.h"

#include "SDL_ttf/include/SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/lib/x86/SDL2_ttf.lib" )

using namespace std;


ModuleUI::ModuleUI() : Module(),
textColor (WHITE)
{
}

// Destructor
ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start(){
	bool res = true;

	//Initialize SDL TTF
	if (TTF_Init() != 0)
	{
		LOG("TTF_Init could not initialize! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	return res;
}

// Called before render is available
bool ModuleUI::Resume()
{
	bool res = true;	

	LOG("Init Image library");

	font = TTF_OpenFont("SpyHunter.ttf", 8);

	//If there was an error in loading the font
	if (font == NULL)
	{
		LOG("TTF_OpenFont could not initialize! SDL_Error: %s\n", SDL_GetError());
		res = false;
	}

	//If everything initialized fine
	return res;
}

// Called before quitting
bool ModuleUI::Stop()
{
	LOG("Freeing textures and Image library");

	//Free the surfaces
	SDL_DestroyTexture(score);
	SDL_DestroyTexture(lives);
	SDL_DestroyTexture(weapons);

	//Close the font that was used
	TTF_CloseFont(font);

	//Quit SDL_ttf
	TTF_Quit();

	return true;
}

// Free texture from memory
update_status ModuleUI::Update()
{
	update_status res = UPDATE_CONTINUE;
	string str_num = to_string(App->player->score).c_str();

	if (App->road->road_state == G_PLAY){
		//Score render
		for (int i = str_num.size(); i < 7; ++i)
			str_num = "0" + str_num;

		if (App->player->block_points){
			str_num = "NO POINTS!";
		}

		score = SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, str_num.c_str(), textColor));

		//Live render
		if (App->player->first_mode != 1000){
			str_num = to_string(1000 - App->player->first_mode).c_str();

			for (int i = str_num.size(); i < 3; ++i)
				str_num = "0" + str_num;
		}
		else{
			str_num = "";
			int i = 0;
			for (i = str_num.size(); i < App->player->lives; ++i)
				str_num = "|" + str_num;
			for (; i < 3; ++i)
				str_num = " " + str_num;
		}
		lives = SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, str_num.c_str(), textColor));

		//Weapon render
		str_num = "";
		if (App->player->turbo_gear == 1){
			str_num = " G1" + str_num;
		}
		else
			str_num = " G2" + str_num;
		if (App->player->truck > 0){
			str_num = "T" + str_num;
		}
		else
			str_num = " " + str_num;
		if (App->player->rocket > 0){
			str_num = "R" + str_num;
		}
		else
			str_num = " " + str_num;
		if (App->player->spray > 0){
			str_num = "S" + str_num;
		}
		else
			str_num = " " + str_num;
		if (App->player->oil > 0){
			str_num = "O" + str_num;
		}
		else
			str_num = " " + str_num;

		weapons = SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, str_num.c_str(), textColor));

		//If there was an error in rendering the text
		if (score == NULL && lives == NULL && weapons == NULL)
		{
			LOG("Cannot build the texture. SDL_CreateTextureFromSurface error: %s", SDL_GetError());
			res = UPDATE_ERROR;
		}

		//Apply the images to the screen
		SDL_Rect test = { 0, 0, 100, 16 };
		App->renderer->Blit(score, 20, 100, &test, 1.0f, RENDER_OTHER);
		test = { 0, 0, 50, 16 };
		App->renderer->Blit(lives, SCREEN_WIDTH / 2 - 25, 100, &test, 1.0f, RENDER_OTHER);
		test = { 0, 0, 80, 16 };
		App->renderer->Blit(weapons, SCREEN_WIDTH - 120, 100, &test, 1.0f, RENDER_OTHER);
	}
	else if (App->road->road_state == G_START){
		SDL_Texture * text =
			SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, "PRESS SPACE TO START", textColor));

		SDL_Rect test = { 0, 0, SCREEN_WIDTH - 40, 20 };
		App->renderer->Blit(text, 20, (SCREEN_HEIGHT / 2) - 10, &test, 1.0f, RENDER_OTHER);

	}
	else if (App->road->road_state == G_PAUSE){
		SDL_Texture * text =
			SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, "PRESS SPACE TO CONTINUE", textColor));

		SDL_Rect test = { 0, 0, SCREEN_WIDTH - 40, 20 };
		App->renderer->Blit(text, 20, (SCREEN_HEIGHT / 2) - 10, &test, 1.0f, RENDER_OTHER);

	}
	else if (App->road->road_state == G_OVER){
		SDL_Texture * text =
			SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, "GAME OVER", textColor));

		SDL_Rect test = { 0, 0, SCREEN_WIDTH - 40, 20 };
		App->renderer->Blit(text, 20, (SCREEN_HEIGHT / 2) - 40, &test, 1.0f, RENDER_OTHER);

		 text =
			SDL_CreateTextureFromSurface(App->renderer->renderer,
			TTF_RenderText_Solid(font, "PRESS SPACE TO START", textColor));

		test = { 0, 0, SCREEN_WIDTH - 40, 20 };
		App->renderer->Blit(text, 20, (SCREEN_HEIGHT / 2) - 10 , &test, 1.0f, RENDER_OTHER);

	}

	

	return res;
}