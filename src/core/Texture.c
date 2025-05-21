#include "core/Texture.h"

int Texture_Load(Texture *texture, Context *context, const char *filename, int cell_width, int cell_height){
	if(context == NULL || filename == NULL || texture == NULL){
		return -1;
	}

	texture->raw = IMG_LoadTexture(context->renderer, filename);

	if(texture->raw == NULL){
		printf("Failed to load texture: %s\n", filename);
		return -1;
	}

	/* Save width and height of the texture. */
	if(SDL_QueryTexture(texture->raw, NULL, NULL, &texture->width, &texture->height) < 0){
		printf("Failed to get texture size.\n");
		return -1;
	}

	texture->num_cells_width = texture->width / cell_width;
	texture->cell_width = cell_width;
	texture->cell_height = cell_height;

	return 0;
}

int Texture_RenderCell(Texture *texture, Context *context, int x, int y, int id){
	SDL_Rect src_rect, dst_rect;

	dst_rect = (SDL_Rect) {x, y, texture->cell_width, texture->cell_height};

	src_rect = (SDL_Rect) {
		(id % texture->num_cells_width) * texture->cell_width,
		(id / texture->num_cells_width) * texture->cell_height,
		texture->cell_width,
		texture->cell_height
	};

	if(SDL_RenderCopy(context->renderer, texture->raw, &src_rect, &dst_rect) < 0){
		printf("Failed to render texture: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}
