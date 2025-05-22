#include <stdio.h>

#include "core/Context.h"
#include "core/Texture.h"
#include "core/Memory.h"

#include "engine/Scene.h"
#include "engine/Gtypes.h"
#include "engine/Game.h"
#include "game/Entities.h"

#define MEMORY_SIZE (4 * 1024 * 1024)

int main(void){
	Context *context;
	Game *game;
	Scene *scene;

	Memory memory;

	Memory_Create(&memory, malloc(MEMORY_SIZE), MEMORY_SIZE);

	context = (Context *) Memory_Alloc(&memory, sizeof(Context));
	game = (Game *) Memory_Alloc(&memory, sizeof(Game));
	scene = (Scene *) Memory_Alloc(&memory, sizeof(Scene));

	printf("Used: %lu KB\nAvailable: %lu KB\n", memory.top / 1024, (memory.size - memory.top) / 1024);

	if(Context_Create(context, "game", 480, 272, 3) < 0)
		exit(1);

	Game_Create(game, context);
	Scene_Create(scene, game);
	Game_SetScene(game, scene);

	scene->world.collision_layer = 1;

	Game_SetUpInputHandler(game, 5);
	Game_BindKey(game, 0, SDL_SCANCODE_D);
	Game_BindKey(game, 1, SDL_SCANCODE_A);
	Game_BindKey(game, 2, SDL_SCANCODE_W);
	Game_BindKey(game, 3, SDL_SCANCODE_S);
	Game_BindKey(game, 4, SDL_SCANCODE_J);

	scene->world.texture = &game->res.textures[1];
	Player_Create(scene);
	Grounder_Create(scene);

	for(int i = 0; i < 20; i++){
		Scene_SetWorldTile(scene, i, 6, 1, 0);
	}

	Scene_SetWorldTile(scene, 0, 5, 1, 0);
	Scene_SetWorldTile(scene, 10, 5, 1, 0);
	Scene_SetWorldTile(scene, 19, 5, 1, 0);

	Texture_Load(
			&game->res.textures[0],
			context,
			"character.png",
			24,
			24
			);

	Texture_Load(
			&game->res.textures[1],
			context,
			"tilemap.png",
			16,
			16
			);

	Texture_Load(
			&game->res.textures[2],
			context,
			"res/entities/bullet.png",
			4,
			4
			);

	Game_Run(game);

	Context_Destroy(context);

	free(memory.data);

	return 0;
}
