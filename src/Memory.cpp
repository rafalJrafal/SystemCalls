#include <stdio.h>

#include "../inc/Memory.h"
#include "../inc/MemoryMap.h"

MemoryMap & memoryMap = MemoryMap::instance();

void * operator new(size_t size) {
	void * m = malloc(size);
	memoryMap.markAlloc(m, size);
	printf("Allocated p = %p size = %d\n", m, size);
	return m;
}
void operator delete(void * p) {
	printf("Deallocated p = %p\n", p);
	free(p);
}

