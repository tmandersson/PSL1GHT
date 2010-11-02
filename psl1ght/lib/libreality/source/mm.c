#include "rsx/reality.h"

int initilized = 0;
gcmConfiguration config;
void *heap_pointer;

// Really dumb allocater
void *realityAllocateAlignedRsxMemory(int alignment, int size) {
	if (!initilized) {
		gcmGetConfiguration(&config);
		initilized = 1;
		heap_pointer = (void *)(uint64_t) config.localAddress;
	}
	void *pointer = heap_pointer;
	pointer = (void *)((((uint64_t) pointer) + (alignment-1)) & (-alignment)); // Align
	if ((uint64_t) pointer + size > config.localAddress + config.localSize) // Out of memory?
		return NULL;
	heap_pointer = (void *)((uint64_t) pointer + size);
	return pointer;
}

void *realityAllocateRsxMemory(int size) {
	return realityAllocateAlignedRsxMemory(size, 0);
}


