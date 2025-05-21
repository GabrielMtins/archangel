#include "game/Entities.h"

Entity * Bullet_Create(Scene *scene){
	Entity *entity = Scene_AddEntity(scene);

	entity->texture = Game_GetTexture(scene->game, 0);
	entity->position.x = 60.0f;
	entity->velocity.x = 80.0f;
	entity->texture_offset = (Vec2) {2.0f, 4.0f};
	entity->hitbox_size = (Vec2) {20.0f, 19.0f};
	entity->collision_mask = 1;

	entity->type = ENTITY_BULLET;

	return entity;
}
