#include "game/Entities.h"

#define TIME_ON_FLOOR 800

static void Jumper_Update(Entity *entity, Scene *scene, float dt);
static void Jumper_Collision(Entity *entity, Entity *other, Scene *scene);
static void Jumper_Think(Entity *entity, Scene *scene);

Entity * Jumper_Create(Scene *scene){
	Entity *entity = Scene_AddEntity(scene);

	entity->texture = Game_GetTexture(scene->game, 0);
	entity->texture_offset = (Vec2) {3.0f, 4.0f};
	entity->hitbox_size = (Vec2) {17.0f, 19.0f};

	entity->velocity.x = 0.0f;
	entity->position.x = 0.0f;
	entity->update = Jumper_Update;
	entity->onCollision = Jumper_Collision;
	entity->think = Jumper_Think;

	entity->collision_layer = 8;
	entity->collision_mask = 1;
	entity->direction.x = 1.0f;
	entity->can_jump = false;

	return entity;
}

static void Jumper_Update(Entity *entity, Scene *scene, float dt){
	(void) scene;
	entity->velocity.y += GRAVITY * dt;

	if(entity->velocity.y != 0.0f){
		entity->direction.y = entity->velocity.y;
	}

	if(entity->velocity.x != 0.0f){
		entity->direction.x = entity->velocity.x;
	}

	if(entity->target == NULL){
		entity->target = Scene_SearchByEntityType(scene, ENTITY_PLAYER);
	}
}

static void Jumper_Collision(Entity *entity, Entity *other, Scene *scene){
	(void) scene;
	(void) other;

	if(entity->velocity.y != 0.0f){
		if(entity->velocity.x == 0.0f){
			entity->velocity.x = entity->direction.x;
		}
		return;
	}

	if(entity->direction.y < 0.0f)
		return;

	if(entity->can_jump)
		return;

	entity->next_think = scene->tick + TIME_ON_FLOOR;
	entity->can_jump = true;
	entity->velocity.x = 0.0f;
}

static void Jumper_Think(Entity *entity, Scene *scene){
	if(!entity->can_jump)
		return;

	entity->can_jump = false;

	entity->velocity.y = -150.0f;

	if(entity->target != NULL){
		entity->velocity.x = (entity->target->position.x - entity->position.x) * 2.0f;
	}
}
