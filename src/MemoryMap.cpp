#include "../inc/MemoryMap.h"

MemoryMap& MemoryMap::instance() {
	static MemoryMap memoryMap;
	return memoryMap;
}

MemoryMap::MemoryMap() {
	
}

MemoryMap::MemoryMap(MemoryMap&) {
	
}

void MemoryMap::markAlloc(void * ptr, size_t size) {
	
}
void MemoryMap::markFree(void * ptr) {
	
}

