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
	entity->collision_mask = 1;

	entity->type = ENTITY_PLAYER;

	return entity;
}

static void Player_Update(Entity *entity, Scene *scene, float dt){
	entity->velocity.x = 0.0f;
	scene->camera.y = -80.0f;

	if(entity->velocity.y != 0.0f){
		if(scene->tick - entity->v.tick_floor > 120)
			entity->v.can_jump = false;

		entity->v.is_falling = entity->velocity.y > 0.0f;
	}

	entity->velocity.y += 400.0f * dt;

	if(Game_GetKey(scene->game, 0))
		entity->velocity.x += 80.0f;

	if(Game_GetKey(scene->game, 1))
		entity->velocity.x += -80.0f;

	if(Game_GetKey(scene->game, 2) && entity->v.can_jump){
		entity->velocity.y = -200.0f;
		entity->v.can_jump = false;
	}

	if(Game_GetKeyDown(scene->game, 4)){
		Entity *bullet = Bullet_Create(scene);
		bullet->position = entity->position;
	}
}

static void Player_Collision(Entity *entity, Entity *other, Scene *scene){
	(void) other;

	if(entity->velocity.y == 0.0f && entity->v.is_falling){
		entity->v.can_jump = true;
		entity->v.tick_floor = scene->tick;
	}
}
