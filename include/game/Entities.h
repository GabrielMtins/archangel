#ifndef ENTITIES_H
#define ENTITIES_H

#include "engine/Gtypes.h"
#include "engine/Game.h"
#include "engine/Scene.h"

enum EntityTypes {
	ENTITY_PLAYER = 0,
	ENTITY_BULLET,
	NUM_ENTITY_TYPES
};

Entity * Player_Create(Scene *scene);

Entity * Bullet_Create(Scene *scene);

#endif
