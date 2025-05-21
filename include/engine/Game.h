#ifndef GAME_H
#define GAME_H

#include "engine/Gtypes.h"

/* TODO
 * Recreate these macros as actual functions
 */

#define Game_GetKey(game, key) InputHandler_GetKey(&game->input_handler, key)
#define Game_GetKeyDown(game, key) InputHandler_GetKeyDown(&game->input_handler, key)
#define Game_GetKeyUp(game, key) InputHandler_GetKeyUp(&game->input_handler, key)
#define Game_SetUpInputHandler(game, keys_used) InputHandler_Create(&game->input_handler, keys_used)
#define Game_BindKey(game, key_id, key_sdl) game->input_handler.key_mapping[key_id] = key_sdl;
#define Game_GetTexture(game, index) &game->res.textures[index]

int Game_Create(Game *game, Context *context);

void Game_SetScene(Game *game, Scene *scene);

void Game_Update(Game *game);

void Game_Render(Game *game);

void Game_Loop(Game *game);

void Game_Run(Game *game);

#endif
