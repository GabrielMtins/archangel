#ifndef ENTITIES_H
#define ENTITIES_H

#include "engine/Gtypes.h"
#include "engine/Game.h"
#include "engine/Scene.h"

#define GRAVITY 400.0f

enum EntityTypes {
	ENTITY_PLAYER = 0,
	ENTITY_BULLET,
	ENTITY_GROUNDER,
	NUM_ENTITY_TYPES
};

Entity * Player_Create(Scene *scene);

Entity * Bullet_Create(Scene *scene);

Entity * Grounder_Create(Scene *scene);

Entity * Jumper_Create(Scene *scene);

#endif
