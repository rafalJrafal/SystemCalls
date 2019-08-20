#include <stdio.h>
#include <new>

#include "../inc/Memory.h"
#include "../inc/MemoryMap.h"


/*
void * operator new(size_t size) throw(std::bad_alloc) {
	printf("new");
	void * m = malloc(size);
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markAlloc(m, size);
	return m;
} */

void * operator new(size_t size, const char * file, int line) {
	void * m = malloc(size);
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markAlloc(m, size, file, line);
	return m;
}

void * operator new [] (size_t size, const char * file, int line) {
	void * m = malloc(size);
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markAlloc(m, size, file, line);
	return m;
}

void operator delete(void * p) _GLIBCXX_USE_NOEXCEPT {
	static MemoryMap & memoryMap = MemoryMap::instance();
	memoryMap.markFree(p);	
	free(p);
}

