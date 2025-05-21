#include "engine/Entity.h"

void Entity_Reset(Entity *entity){
	entity->position = (Vec2) {0.0f, 0.0f};
	entity->velocity = (Vec2) {0.0f, 0.0f};

	entity->hitbox_size = (Vec2) {0.0f, 0.0f};

	entity->health = 100;
	entity->state = 0;
	entity->type = -1;
	entity->next_think = 0;

	entity->collision_layer = 0;
	entity->collision_mask = 0;
	
	entity->texture = NULL;
	entity->hud_element = false;

	entity->texture_offset = (Vec2) {0.0f, 0.0f};

	entity->update = NULL;
	entity->onCollision = NULL;
	entity->think = NULL;

	entity->target = NULL;
	entity->child = NULL;
	entity->parent = NULL;
	
	entity->next = NULL;

	entity->removed = false;
	entity->free = false;
}
