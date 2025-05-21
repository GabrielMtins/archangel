#ifndef SCENE_H
#define SCENE_H

#include "engine/Gtypes.h"

void Scene_Create(Scene *scene, Game *game);

void Scene_Update(Scene *scene, uint32_t delta_tick);

void Scene_Render(Scene *scene, Context *context);

Entity * Scene_FindEntityType(Scene *scene, int type);

Entity * Scene_AddEntity(Scene *scene);

void Scene_SolveEntityCollision(Scene *scene, Entity *entity, Entity *other);

void Scene_SetWorldTile(Scene *scene, int x, int y, int layer, Tile id);

Tile Scene_GetWorldTile(Scene *scene, int x, int y, int layer);

#endif
