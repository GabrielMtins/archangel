#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *target;

	int internal_width, internal_height;

	bool quit;
} Context;

int Context_Create(Context *context, const char *window_name, int width, int height, int scale);

int Context_PollEvent(Context *context);

void Context_RenderPresent(Context *context);

void Context_Destroy(Context *context);

#endif
