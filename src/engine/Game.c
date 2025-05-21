#include "engine/Game.h"
#include "engine/Scene.h"
#include "core/Draw.h"

int Game_Create(Game *game, Context *context){
	game->context = context;
	game->main_scene = NULL;
	game->tick = 0;
	InputHandler_Create(&game->input_handler, 0);

	return 1;
}

void Game_SetScene(Game *game, Scene *scene){
	game->main_scene = scene;
}

void Game_Update(Game *game){
	uint32_t new_tick;
	uint32_t delta_tick;

	new_tick = SDL_GetTicks();
	delta_tick = (new_tick - game->tick);
	game->tick = new_tick;

	InputHandler_Update(&game->input_handler);
	Scene_Update(game->main_scene, delta_tick);
}

void Game_Render(Game *game){
	Draw_ClearScreen(game->context, 0x00, 0x00, 0x00, 0xff);

	Scene_Render(game->main_scene, game->context);

	Context_RenderPresent(game->context);
}

void Game_Loop(Game *game){
	Context_PollEvent(game->context);
	Game_Update(game);
	Game_Render(game);
}

void Game_Run(Game *game){
	while(!game->context->quit)
		Game_Loop(game);
}
