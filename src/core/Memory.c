#include "core/Memory.h"

void Memory_Create(Memory *memory, void *data, size_t size){
	memory->data = (uint8_t *) data;
	memory->size = size;
	memory->top = 0;
}

void * Memory_Alloc(Memory *memory, size_t size){
	void *data_alloc;

	if(memory->top + size > memory->size)
		return NULL;

	data_alloc = (void *) (memory->data + memory->top);

	memory->top += size;

	return data_alloc;
}
