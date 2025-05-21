#include "core/Draw.h"

int Draw_ClearScreen(Context *context, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	SDL_SetRenderDrawColor(
			context->renderer,
			r,
			g,
			b,
			a
			);

	SDL_RenderClear(context->renderer);

	return 0;
}
