#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_KEYS 64

typedef struct {
	int key_mapping[MAX_KEYS];
	int keys_used;

	bool key_state[MAX_KEYS];
	uint32_t key_down_tick[MAX_KEYS];
	uint32_t key_up_tick[MAX_KEYS];

	uint32_t current_tick;
} InputHandler;

void InputHandler_Create(InputHandler *handler, int keys_used);

void InputHandler_Update(InputHandler *handler);

bool InputHandler_GetKey(InputHandler *handler, int key);

bool InputHandler_GetKeyDown(InputHandler *handler, int key);

bool InputHandler_GetKeyUp(InputHandler *handler, int key);

#endif
