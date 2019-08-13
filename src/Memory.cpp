#include <stdio.h>

#include "../inc/Memory.h"
#include "../inc/MemoryMap.h"



void * operator new(size_t size) {
	void * m = malloc(size);
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markAlloc(m, size);
	return m;
}
void operator delete(void * p) {
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markFree(p);	
	free(p);
}

