#include "engine/Scene.h"
#include "core/Box.h"
#include "engine/Entity.h"

static int Scene_GetTileIndex(int x, int y, int layer);
static bool Scene_CheckCollisionEntityWorld(Scene *scene, Entity *entity);
static void Scene_UpdateEntities(Scene *scene, float dt);
static void Scene_RenderEntities(Scene *scene, Context *context);
static void Scene_RenderTile(Scene *scene, Context *context, int x, int y, int layer);
static void Scene_RenderWorld(Scene *scene, Context *context, int layer);
static void Scene_HandleEntityCollision(Scene *scene);
static void Scene_RemoveEntity(Scene *scene, size_t id);

void Scene_Create(Scene *scene, Game *game){
	scene->game = game;
	scene->num_entities = 0;
	scene->num_removed = 0;

	for(int i = 0; i < WORLD_DATA_SIZE; i++)
		scene->world.tiles[i] = -1;

	scene->tick = 0;

	scene->camera = (Vec2) {0.0f, 0.0f};
}

void Scene_Update(Scene *scene, uint32_t delta_tick){
	float dt = 0.001f * delta_tick;
	scene->tick += delta_tick;

	Scene_UpdateEntities(scene, dt);
	Scene_HandleEntityCollision(scene);
}

void Scene_Render(Scene *scene, Context *context){
	Scene_RenderWorld(scene, context, WORLD_BACKGROUND_LAYER);
	Scene_RenderEntities(scene, context);
	Scene_RenderWorld(scene, context, WORLD_FOREGROUND_LAYER);
}

Entity * Scene_SearchByEntityType(Scene *scene, int type){
	Entity *found = NULL;
	Entity *current;

	for(size_t i = 0; i < scene->num_entities; i++){
		current = &scene->entities[i];

		if(current->removed)
			continue;

		if(current->type != type)
			continue;

		if(found == NULL){
			found = current;
		}
		else{
			found->next = current;
			found = found->next;
		}

		found->next = NULL;
	}

	return found;
}

Entity * Scene_AddEntity(Scene *scene){
	Entity *new_entity;

	if(scene->num_removed > 0){
		new_entity = scene->removed[--scene->num_removed];
	}
	else{
		new_entity = &scene->entities[scene->num_entities++];
	}

	Entity_Reset(new_entity);

	return new_entity;
}

void Scene_SolveEntityCollision(Scene *scene, Entity *entity, Entity *other){
	Vec2 og_pos;
	bool solved_x_axis;

	og_pos = entity->position;

	Box_SolveCollision(&entity->position, &entity->hitbox_size, &other->position, &other->hitbox_size, &solved_x_axis);

	if(!Scene_CheckCollisionEntityWorld(scene, entity)){
		if(solved_x_axis)
			entity->velocity.x = 0.0f;
		else
			entity->velocity.y = 0.0f;

		return;
	}
	/* If the entity was pushed to collide with a world tile,
	 * revert to the original position. */

	entity->position = og_pos;
	og_pos = other->position;

	Box_SolveCollision(&other->position, &other->hitbox_size, &entity->position, &entity->hitbox_size, NULL);

	if(!Scene_CheckCollisionEntityWorld(scene, other)){
		if(solved_x_axis)
			other->velocity.x = 0.0f;
		else
			other->velocity.y = 0.0f;

		return;
	}
	/* If the other was pushed to collide with a world tile,
	 * revert to the original position. */

	other->position = og_pos;
}

void Scene_SetWorldTile(Scene *scene, int x, int y, int layer, Tile id){
	int index;

	index = Scene_GetTileIndex(x, y, layer);

	if(index < 0)
		return;

	scene->world.tiles[index] = id;
}

Tile Scene_GetWorldTile(Scene *scene, int x, int y, int layer){
	int index;

	index = Scene_GetTileIndex(x, y, layer);

	if(index < 0)
		return -1;

	return scene->world.tiles[index];
}

static int Scene_GetTileIndex(int x, int y, int layer){
	if(x < 0 || y < 0 || x >= WORLD_WIDTH || y >= WORLD_HEIGHT || layer < 0 || layer >= WORLD_LAYERS)
		return -1;

	return (x + y * WORLD_WIDTH) + layer * WORLD_WIDTH * WORLD_HEIGHT;
}

static bool Scene_CheckCollisionEntityWorld(Scene *scene, Entity *entity){
	int start_x, start_y, size_x, size_y;
	Vec2 pos, size;

	if((entity->collision_mask & scene->world.collision_layer) == 0)
		return false;

	start_x = (int) (entity->position.x / TILE_WIDTH);
	start_y = (int) (entity->position.y / TILE_HEIGHT);

	size_x = (int) (entity->hitbox_size.x / TILE_WIDTH) + 1;
	size_y = (int) (entity->hitbox_size.y / TILE_HEIGHT) + 1;

	for(int i = start_x; i <= start_x + size_x; i++){
		for(int j = start_y; j <= start_y + size_y; j++){
			if(Scene_GetWorldTile(scene, i, j, WORLD_FOREGROUND_LAYER) == -1)
				continue;

			pos = (Vec2) {i * TILE_WIDTH, j * TILE_HEIGHT};
			size = (Vec2) {TILE_WIDTH, TILE_HEIGHT};

			if(Box_CheckCollisionBoxBox(&pos, &size, &entity->position, &entity->hitbox_size))
				return true;
		}
	}

	return false;
}

static void Scene_UpdateEntities(Scene *scene, float dt){
	Entity *current_entity;
	bool found_collision;

	for(size_t i = 0; i < scene->num_entities; i++){
		found_collision = false;
		current_entity = &scene->entities[i];

		if(current_entity->free)
			Scene_RemoveEntity(scene, i);

		if(current_entity->removed)
			continue;

		current_entity->position.x += current_entity->velocity.x * dt;

		if(Scene_CheckCollisionEntityWorld(scene, current_entity)){
			float min_x = ceilf(current_entity->position.x / TILE_WIDTH);
			float max_x = floorf((current_entity->position.x + current_entity->hitbox_size.x) / TILE_WIDTH);

			if(current_entity->velocity.x < 0.0f)
				current_entity->position.x = min_x * TILE_WIDTH;
			else
				current_entity->position.x = max_x * TILE_WIDTH - current_entity->hitbox_size.x * 1.01f;

			current_entity->velocity.x = 0.0f;
			found_collision = true;
		}

		current_entity->position.y += current_entity->velocity.y * dt;

		if(Scene_CheckCollisionEntityWorld(scene, current_entity)){
			float min_y = ceilf(current_entity->position.y / TILE_HEIGHT);
			float max_y = floorf((current_entity->position.y + current_entity->hitbox_size.y) / TILE_HEIGHT);

			if(current_entity->velocity.y < 0.0f)
				current_entity->position.y = min_y * TILE_HEIGHT;
			else
				current_entity->position.y = max_y * TILE_HEIGHT - current_entity->hitbox_size.y * 1.01f;

			current_entity->velocity.y = 0.0f;
			found_collision = true;
		}

		if(found_collision && current_entity->onCollision != NULL)
			current_entity->onCollision(current_entity, NULL, scene);

		if(current_entity->update != NULL)
			current_entity->update(current_entity, scene, dt);

		if(current_entity->think != NULL && scene->tick > current_entity->next_think)
			current_entity->think(current_entity, scene);
	}
}

static void Scene_RenderEntities(Scene *scene, Context *context){
	Entity *current_entity;
	Vec2 start, end;

	for(size_t i = 0; i < scene->num_entities; i++){
		current_entity = &scene->entities[i];

		if(current_entity->removed)
			continue;

		if(current_entity->texture == NULL)
			continue;

		Vec2_Sub(&start, &current_entity->position, &current_entity->texture_offset);

		if(!current_entity->hud_element)
			Vec2_Sub(&start, &start, &scene->camera);

		end.x = start.x + current_entity->texture->cell_width;
		end.y = start.y + current_entity->texture->cell_height;

		if(end.x < 0 || end.y < 0 || start.x > context->internal_width || start.y > context->internal_height)
			continue;

		Texture_RenderCell(
				current_entity->texture,
				context,
				floorf(start.x),
				floorf(start.y),
				current_entity->cell
				);
	}
}

static void Scene_RenderTile(Scene *scene, Context *context, int x, int y, int layer){
	Vec2 pos;
	Tile tile_id;

	if(scene->world.texture == NULL)
		return;

	tile_id = Scene_GetWorldTile(scene, x, y, layer);

	if(tile_id < 0)
		return;

	pos = (Vec2) {x * TILE_WIDTH, y * TILE_HEIGHT};
	Vec2_Sub(&pos, &pos, &scene->camera);

	Texture_RenderCell(
			scene->world.texture,
			context,
			pos.x,
			pos.y,
			tile_id
			);
}

static void Scene_RenderWorld(Scene *scene, Context *context, int layer){
	int camera_x = scene->camera.x / TILE_WIDTH;
	int camera_y = scene->camera.y / TILE_HEIGHT;

	for(int i = -1; i < context->internal_width / TILE_WIDTH + 1; i++){
		for(int j = -1; j < context->internal_width / TILE_WIDTH + 1; j++){
			Scene_RenderTile(scene, context, i + camera_x, j + camera_y, layer);
		}
	}
}

static void Scene_HandleEntityCollision(Scene *scene){
	Entity *current, *other;
	bool mask, trigger;

	for(size_t i = 0; i < scene->num_entities; i++){
		current = &scene->entities[i];

		if(current->removed)
			continue;

		if(current->collision_mask == 0 && current->collision_trigger == 0)
			continue;

		for(size_t j = 0; j < scene->num_entities; j++){
			if(i == j)
				continue;

			other = &scene->entities[j];

			if(other->removed)
				continue;

			mask = current->collision_mask & other->collision_layer;
			trigger = current->collision_trigger & other->collision_layer;

			if(!mask && !trigger)
				continue;

			if(!Box_CheckCollisionBoxBox(&current->position, &current->hitbox_size, &other->position, &other->hitbox_size))
				continue;

			if(mask){
				Scene_SolveEntityCollision(scene, current, other);
			}

			if(current->onCollision != NULL)
				current->onCollision(current, other, scene);

			if(other->onCollision != NULL && mask)
				other->onCollision(other, current, scene);
		}
	}
}

static void Scene_RemoveEntity(Scene *scene, size_t id){
	scene->entities[id].free = false;
	scene->entities[id].removed = true;
	scene->removed[scene->num_removed++] = &scene->entities[id];
}
