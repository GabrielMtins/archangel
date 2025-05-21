#ifndef TEXTURE_H
#define TEXTURE_H

#include "Context.h"

typedef struct {
	SDL_Texture *raw;
	int width, height;
	int num_cells_width;
	int cell_width, cell_height;
} Texture;

int Texture_Load(Texture *texture, Context *context, const char *filename, int cell_width, int cell_height);

int Texture_RenderCell(Texture *texture, Context *context, int x, int y, int id);

#endif
