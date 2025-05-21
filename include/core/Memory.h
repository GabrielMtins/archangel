#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint8_t *data;
	size_t size;
	size_t top;
} Memory;

void Memory_Create(Memory *memory, void *data, size_t size);

void * Memory_Alloc(Memory *memory, size_t size);

#endif
