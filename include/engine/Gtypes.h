#ifndef GTYPES_H
#define GTYPES_H

#include "core/Context.h"
#include "core/Texture.h"
#include "core/InputHandler.h"
#include "core/Vec2.h"

#define MAX_ENTITIES 1024
#define MAX_TEXTURES 256

#define WORLD_WIDTH 512
#define WORLD_HEIGHT 512
#define WORLD_LAYERS 2
#define WORLD_BACKGROUND_LAYER 0
#define WORLD_FOREGROUND_LAYER 1

#define WORLD_DATA_SIZE (WORLD_WIDTH * WORLD_HEIGHT * WORLD_LAYERS)

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define MAX_TIMERS 4

typedef int8_t Tile;

typedef struct game_s Game;
typedef struct scene_s Scene;
typedef struct entity_s Entity;

enum PauseMode {
	PAUSE_MODE_PAUSABLE = 0,
	PAUSE_MODE_ALWAYS,
	PAUSE_MODE_WHENPAUSED,
};

typedef struct {
	Texture textures[MAX_TEXTURES];
} Resources;

struct entity_s {
	Vec2 position;
	Vec2 velocity;
	Vec2 direction;

	Vec2 hitbox_size;

	/* When health <= 0, the entity is marked to be freed. */
	int health;
	/* Used for state machines. */
	int state;

	int type;

	int pause_mode;

	/* Tick when the think() function will be called again. */
	uint32_t next_think;

	bool active;

	/* A mask of collision layers. */
	uint32_t collision_layer;
	/* A mask which contains which layers the entity
	 * can collide with. */
	uint32_t collision_mask;

	/* A mask whcih contains which layers the entity can trigger
	 * its onCollision() function. */
	uint32_t collision_trigger;

	Texture *texture;

	/* Mark as true so that the texture will not
	 * be rendered considering the camera position.
	 * Useful for hud elements. */
	bool hud_element;

	/* Cell of the current texture, use for animations */
	int cell;

	/* Offset of the texture in relation to position. */
	Vec2 texture_offset;

	/* Update function called every frame */
	void (*update)(Entity *, Scene *, float);

	/* Think function, called when current_tick > next_think. */
	void (*think)(Entity *, Scene *);

	/* Collision function called when entity collides with another
	 * The first entity is the entity which the collision occured.
	 * When the second entity is NULL, the collision happened with
	 * the world. */
	void (*onCollision)(Entity*, Entity*, Scene *);

	/* Target: an enemy, for example. */
	Entity *target;
	Entity *child;
	Entity *parent;

	/* Used for linked lists when searching. */
	Entity *next;

	/* Used internally to indicate when the entity slot is available. */
	bool removed;
	/* When this flag is marked as true, the entity will be removed 
	 * next frame. */
	bool free;

	/* --------- END OF DEFAULT PROPERTIES --------- */

	/* Add your custom properties here.
	 * ... */

	bool can_jump;
	uint32_t tick_floor;
	uint32_t timers[MAX_TIMERS];
};

typedef struct {
	Tile tiles[WORLD_WIDTH * WORLD_HEIGHT * WORLD_LAYERS];
	uint32_t collision_layer;
	Texture *texture;
} World;

struct game_s {
	Context *context;
	Scene *main_scene;
	Resources res;

	InputHandler input_handler;
	uint32_t tick;
};

struct scene_s {
	Game *game;
	
	World world;

	Entity entities[MAX_ENTITIES];
	size_t num_entities;

	Entity *removed[MAX_ENTITIES];
	size_t num_removed;

	Vec2 camera;
	uint32_t tick;
};

#endif
