#include "Globals.h"
#include "Application.h"
#include "ModuleRoad.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// Background / ship
	background_ship.x = 10;
	background_ship.y = 24;
	background_ship.w = 522;
	background_ship.h = 181;

	mooring_f.x = 761;
	mooring_f.y = 176;
	mooring_f.w = 31;
	mooring_f.h = 24;

	mooring_b.x = 800;
	mooring_b.y = 184;
	mooring_b.w = 21;
	mooring_b.h = 16;

	int i = 24;
	boat.frames.push_back({ 10,  i, 522, 181 });
	boat.frames.push_back({ 10, ++i, 522, 181 });
	boat.frames.push_back({ 10, ++i, 522, 181 });
	boat.frames.push_back({ 10, ++i, 522, 181 });
	boat.frames.push_back({ 10, --i, 522, 181 });
	boat.frames.push_back({ 10, --i, 522, 181 });
	boat.speed = 0.03f;

	// flag animation
	flag.frames.push_back({ 848, 208, 40, 40 });
	flag.frames.push_back({ 848, 256, 40, 40 });
	flag.frames.push_back({ 848, 304, 40, 40 });
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({ 624, 16, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.frames.push_back({ 624, 144 + 1, 32, 56 });
	girl.frames.push_back({ 624, 80 + 1, 32, 56 });
	girl.frames.push_back({ 624, 16 + 2, 32, 56 });
	girl.frames.push_back({ 624, 80 + 2, 32, 56 });
	girl.frames.push_back({ 624, 144 + 3, 32, 56 });
	girl.frames.push_back({ 624, 80 + 3, 32, 56 });
	girl.frames.push_back({ 624, 16 + 2, 32, 56 });
	girl.frames.push_back({ 624, 80 + 2, 32, 56 });
	girl.frames.push_back({ 624, 144 + 1, 32, 56 });
	girl.frames.push_back({ 624, 80 + 1, 32, 56 });
	girl.speed = 0.06f;

	pair.frames.push_back({ 552, 8, 64, 64 });
	pair.frames.push_back({ 552, 72, 64, 64 });
	pair.frames.push_back({ 552, 136+1, 64, 64 });
	pair.frames.push_back({ 552, 72+1, 64, 64 });
	pair.frames.push_back({ 552, 8+2, 64, 64 });
	pair.frames.push_back({ 552, 72+2, 64, 64 });
	pair.frames.push_back({ 552, 136+3, 64, 64 });
	pair.frames.push_back({ 552, 72+3, 64, 64 });
	pair.frames.push_back({ 552, 8+2, 64, 64 });
	pair.frames.push_back({ 552, 72+2, 64, 64 });
	pair.frames.push_back({ 552, 136+1, 64, 64 });
	pair.frames.push_back({ 552, 72+1, 64, 64 });
	pair.speed = 0.06f;

	green.frames.push_back({ 665, 16, 32, 56 });
	green.frames.push_back({ 665, 80, 32, 56 });
	green.frames.push_back({ 665, 16 + 1, 32, 56 });
	green.frames.push_back({ 665, 80 + 1, 32, 56 });
	green.frames.push_back({ 665, 16 + 2, 32, 56 });
	green.frames.push_back({ 665, 80 + 2, 32, 56 });
	green.frames.push_back({ 665, 16 + 3, 32, 56 });
	green.frames.push_back({ 665, 80 + 3, 32, 56 });
	green.frames.push_back({ 665, 16 + 2, 32, 56 });
	green.frames.push_back({ 665, 80 + 2, 32, 56 });
	green.frames.push_back({ 665, 16 + 1, 32, 56 });
	green.frames.push_back({ 665, 80 + 1, 32, 56 });
	green.speed = 0.06f;

	blue.frames.push_back({ 704, 16, 48, 56 });
	blue.frames.push_back({ 704, 80, 48, 56 });
	blue.frames.push_back({ 704, 144 +1, 48, 56 });
	blue.frames.push_back({ 704, 80+1, 48, 56 });
	blue.frames.push_back({ 704, 16+2, 48, 56 });
	blue.frames.push_back({ 704, 80+2, 48, 56 });
	blue.frames.push_back({ 704, 144+3, 48, 56 });
	blue.frames.push_back({ 704, 80+3, 48, 56 });
	blue.frames.push_back({ 704, 16+2, 48, 56 });
	blue.frames.push_back({ 704, 80+2, 48, 56 });
	blue.frames.push_back({ 704, 144+1, 48, 56 });
	blue.frames.push_back({ 704, 80+1, 48, 56 });
	blue.speed = 0.06f;

	brown.frames.push_back({ 761, 16, 40, 40 });
	brown.frames.push_back({ 761, 64, 40, 40 });
	brown.frames.push_back({ 761, 112+1, 40, 40 });
	brown.frames.push_back({ 761, 64+1, 40, 40 });
	brown.frames.push_back({ 761, 16+2, 40, 40 });
	brown.frames.push_back({ 761, 64+2, 40, 40 });
	brown.frames.push_back({ 761, 112+3, 40, 40 });
	brown.frames.push_back({ 761, 64+3, 40, 40 });
	brown.frames.push_back({ 761, 16+2, 40, 40 });
	brown.frames.push_back({ 761, 64+2, 40, 40 });
	brown.frames.push_back({ 761, 112+1, 40, 40 });
	brown.frames.push_back({ 761, 64+1, 40, 40 });
	brown.speed = 0.06f;

	pink.frames.push_back({ 808, 24, 48, 32 });
	pink.frames.push_back({ 808, 72, 48, 32 });
	pink.frames.push_back({ 808, 120+1, 48, 32 });
	pink.frames.push_back({ 808, 72+1, 48, 32 });
	pink.frames.push_back({ 808, 24+2, 48, 32 });
	pink.frames.push_back({ 808, 72+2, 48, 32 });
	pink.frames.push_back({ 808, 120+3, 48, 32 });
	pink.frames.push_back({ 808, 72+3, 48, 32 });
	pink.frames.push_back({ 808, 24+2, 48, 32 });
	pink.frames.push_back({ 808, 72+2, 48, 32 });
	pink.frames.push_back({ 808, 120+1, 48, 32 });
	pink.frames.push_back({ 808, 72+1, 48, 32 });
	pink.speed = 0.06f;

}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg", 1);
	
	return graphics!=NULL;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, 0, &(boat.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 190, 104, &(girl.GetCurrentFrame()), 0.75f); // flag animation
	App->renderer->Blit(graphics, 126, 96, &(pair.GetCurrentFrame()), 0.75f);
	App->renderer->Blit(graphics, 223, 104, &(green.GetCurrentFrame()), 0.75f);
	App->renderer->Blit(graphics, 286, 96, &(blue.GetCurrentFrame()), 0.75f);
	App->renderer->Blit(graphics, 87, 24, &(brown.GetCurrentFrame()), 0.75f);
	App->renderer->Blit(graphics, 128, 24, &(pink.GetCurrentFrame()), 0.75f);


	App->renderer->Blit(graphics, 0, 170, &ground);
	App->renderer->Blit(graphics, 90, 200, &mooring_f);
	App->renderer->Blit(graphics, 240, 160, &mooring_b);
	App->renderer->Blit(graphics, 435, 200, &mooring_f);
	App->renderer->Blit(graphics, 435, 160, &mooring_b);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}