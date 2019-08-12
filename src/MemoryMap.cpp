#include "../inc/MemoryMap.h"
#include "../../LogSystem/inc/LogSystem.h"

MemoryMap& MemoryMap::instance() {
	static MemoryMap memoryMap;
	return memoryMap;
}

MemoryMap::MemoryMap() {
	
}

MemoryMap::MemoryMap(MemoryMap&) {
	
}

void MemoryMap::markAlloc(void * ptr, size_t size) {
	LogSystem::LogSystem::memLog("Allocated memory at ptr = %p size = %d", ptr, size);
	struct MemoryAllocation mem;
	
}
void MemoryMap::markFree(void * ptr) {
		LogSystem::LogSystem::memLog("Deallocated memory at ptr = %p", ptr);
}

