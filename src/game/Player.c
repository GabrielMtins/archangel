#include "game/Entities.h"

static void Player_Update(Entity *entity, Scene *scene, float dt);
static void Player_Collision(Entity *entity, Entity *other, Scene *scene);

Entity * Player_Create(Scene *scene){
	Entity *entity = Scene_AddEntity(scene);

	entity->texture = Game_GetTexture(scene->game, 0);
	entity->update = Player_Update;
	entity->onCollision = Player_Collision;
	entity->position.x = 60.0f;
	entity->texture_offset = (Vec2) {3.0f, 4.0f};
	entity->hitbox_size = (Vec2) {17.0f, 19.0f};
	entity->collision_layer = 2;
	entity->collision_mask = 1;
	entity->collision_trigger = 8;

	entity->type = ENTITY_PLAYER;

	return entity;
}

static void Player_Update(Entity *entity, Scene *scene, float dt){
	entity->velocity.x = 0.0f;
	scene->camera.y = -80.0f;

	if(entity->velocity.y != 0.0f){
		if(scene->tick - entity->tick_floor > 120)
			entity->can_jump = false;

		entity->direction.y = entity->velocity.y;
	}

	entity->velocity.y += GRAVITY * dt;

	if(Game_GetKey(scene->game, 0))
		entity->velocity.x += 80.0f;

	if(Game_GetKey(scene->game, 1))
		entity->velocity.x += -80.0f;

	if(Game_GetKey(scene->game, 2) && entity->can_jump){
		entity->velocity.y = -200.0f;
		entity->can_jump = false;
	}

	if(Game_GetKeyDown(scene->game, 4)){
		Entity *bullet = Bullet_Create(scene);
		bullet->position = entity->position;
	}
}

static void Player_Collision(Entity *entity, Entity *other, Scene *scene){
	(void) other;
	(void) scene;

	if(entity->velocity.y == 0.0f){
		if(entity->direction.y > 0.0f){
			entity->can_jump = true;
			entity->tick_floor = scene->tick;
		}
		else{
			entity->velocity.y = entity->direction.y;
		}
	}
}
