#include "game/Entities.h"

static void Grounder_Update(Entity *entity, Scene *scene, float dt);
static void Grounder_Collision(Entity *entity, Entity *other, Scene *scene);

Entity * Grounder_Create(Scene *scene){
	Entity *entity = Scene_AddEntity(scene);

	entity->texture = Game_GetTexture(scene->game, 0);
	entity->texture_offset = (Vec2) {3.0f, 4.0f};
	entity->hitbox_size = (Vec2) {17.0f, 19.0f};

	entity->velocity.x = 100.0f;
	entity->position.x = 0.0f;
	entity->update = Grounder_Update;
	entity->onCollision = Grounder_Collision;

	entity->collision_mask = 3;
	entity->direction.x = 1.0f;

	return entity;
}

static void Grounder_Update(Entity *entity, Scene *scene, float dt){
	(void) (scene);

	entity->velocity.y += GRAVITY * dt;

	/*
	if(entity->target == NULL){
		entity->target = Scene_SearchByEntityType(scene, ENTITY_PLAYER);
	}

	if(entity->target != NULL){
		if(entity->target->position.x > entity->position.x){
			entity->velocity.x = 50.0f;
		}
		else{
			entity->velocity.x = -50.0f;
		}
	}
	*/
}

static void Grounder_Collision(Entity *entity, Entity *other, Scene *scene){
	(void) scene;
	(void) other;

	if(entity->velocity.x != 0.0f)
		return;

	entity->direction.x *= -1.0f;
	entity->velocity.x = entity->direction.x * 100.0f;

	/*
	if(entity->velocity.y == 0.0f && entity->velocity.x == 0.0f){
		entity->velocity.y = -150.0f;
	}
	*/
}
