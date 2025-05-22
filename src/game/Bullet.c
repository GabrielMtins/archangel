#include "game/Entities.h"

#define BULLET_TIME_ALIVE 2000

static void Bullet_Think(Entity *entity, Scene *scene);
static void Bullet_Collision(Entity *entity, Entity *other, Scene *scene);

Entity * Bullet_Create(Scene *scene){
	Entity *entity = Scene_AddEntity(scene);

	entity->texture = Game_GetTexture(scene->game, 2);
	entity->position.x = 60.0f;
	entity->velocity.x = 300.0f;
	entity->texture_offset = (Vec2) {0.0f, 0.0f};
	entity->hitbox_size = (Vec2) {4.0f, 4.0f};
	entity->collision_mask = 1;

	entity->think = Bullet_Think;
	entity->onCollision = Bullet_Collision;

	entity->type = ENTITY_BULLET;

	entity->next_think = scene->tick + BULLET_TIME_ALIVE;

	printf("%lu\n", scene->num_removed);

	return entity;
}

static void Bullet_Think(Entity *entity, Scene *scene){
	(void) scene;
	entity->free = true;
}

static void Bullet_Collision(Entity *entity, Entity *other, Scene *scene){
	(void) other;
	(void) scene;

	entity->free = true;
}
