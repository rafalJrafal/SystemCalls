#include <stdio.h>

#include "../inc/Memory.h"
#include "../inc/MemoryMap.h"

MemoryMap & memoryMap = MemoryMap::instance();

void * operator new(size_t size) {
	void * m = malloc(size);
	memoryMap.markAlloc(m, size);
	return m;
}
void operator delete(void * p) {
	memoryMap.markFree(p);	
	free(p);
}

