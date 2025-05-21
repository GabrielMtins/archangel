#include "core/Context.h"
#include "SDL_render.h"

int Context_Create(Context *context, const char *window_name, int width, int height, int scale){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	if(IMG_Init(IMG_INIT_PNG) < 0){
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	context->window = SDL_CreateWindow(
			window_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width * scale,
			height * scale,
			SDL_WINDOW_RESIZABLE
			);

	context->internal_width = width;
	context->internal_height = height;

	if(context->window == NULL){
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	context->renderer = SDL_CreateRenderer(
			context->window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
			);

	if(context->renderer == NULL){
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	context->target = SDL_CreateTexture(
			context->renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			width,
			height
			);

	if(context->target == NULL){
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetRenderTarget(context->renderer, context->target);

	context->quit = false;

	return 0;
}

int Context_PollEvent(Context *context){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			context->quit = true;
	}

	return 0;
}

void Context_RenderPresent(Context *context){
	SDL_SetRenderTarget(context->renderer, NULL);
	SDL_RenderCopy(context->renderer, context->target, NULL, NULL);

	SDL_RenderPresent(context->renderer);

	SDL_SetRenderTarget(context->renderer, context->target);
}

void Context_Destroy(Context *context){
	SDL_DestroyTexture(context->target);
	SDL_DestroyRenderer(context->renderer);
	SDL_DestroyWindow(context->window);

	IMG_Quit();
	SDL_Quit();
}
