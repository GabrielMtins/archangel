#include "core/InputHandler.h"

void InputHandler_Create(InputHandler *handler, int keys_used){
	handler->keys_used = keys_used;

	for(int i = 0; i < handler->keys_used; i++){
		handler->key_state[i] = 0;
		handler->key_down_tick[i] = 0;
		handler->key_up_tick[i] = 0;
	}

	handler->current_tick = 0;
}

void InputHandler_Update(InputHandler *handler){
	handler->current_tick = SDL_GetTicks();
	const uint8_t *keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < handler->keys_used; i++){
		int current_key = handler->key_mapping[i];
		int key_down = keys[current_key];

		if(key_down && !handler->key_state[i]){
			handler->key_down_tick[i] = handler->current_tick;
		}

		if(!key_down && handler->key_state[i]){
			handler->key_up_tick[i] = handler->current_tick;
		}

		handler->key_state[i] = key_down;
	}
}

bool InputHandler_GetKey(InputHandler *handler, int key){
	return handler->key_state[key];
}

bool InputHandler_GetKeyDown(InputHandler *handler, int key){
	return handler->key_down_tick[key] == handler->current_tick;
}

bool InputHandler_GetKeyUp(InputHandler *handler, int key){
	return handler->key_up_tick[key] == handler->current_tick;
}
