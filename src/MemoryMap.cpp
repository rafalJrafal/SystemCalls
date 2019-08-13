#include "../inc/MemoryMap.h"
#include "../../LogSystem/inc/LogSystem.h"

MemoryMap& MemoryMap::instance() {
	static MemoryMap memoryMap;
	return memoryMap;
}

MemoryMap::MemoryMap() : mFirst(0) {
	
}

MemoryMap::MemoryMap(MemoryMap&) {
	
}

void MemoryMap::markAlloc(void * ptr, size_t size) {
	LogSystem::LogSystem::memLog("Allocated memory at ptr = %p size = %d.", ptr, size);
	struct MemoryAllocation mem;// = (MemoryAllocation*)malloc(sizeof(MemoryAllocation));
	mem.address = ptr;
	mem.size = size;
	mem.isAllocated = true;
	addMemoryItem(MemoryAllocationItem(mem));
	printMemory();
}
void MemoryMap::markFree(void * ptr) {
	LogSystem::LogSystem::memLog("Deallocated memory at ptr = %p", ptr);
}

void MemoryMap::addMemoryItem(MemoryAllocationItem item) {
	if (mFirst == 0) {
		mFirst = (MemoryAllocationItem*)malloc(sizeof(MemoryAllocationItem));
		mFirst->address = item.address;
		mFirst->size = item.size;
		mFirst->isAllocated = item.isAllocated;
		mFirst->nextItem = 0;
	}
	else {
		MemoryAllocationItem * newElement = (MemoryAllocationItem*)malloc(sizeof(MemoryAllocationItem));
		newElement->address = item.address;
		newElement->size = item.size;
		newElement->isAllocated = item.isAllocated;
		newElement->nextItem = 0;
		MemoryAllocationItem * last = mFirst;
		while (last->nextItem != 0) {
			last = last->nextItem;
		}
		last->nextItem = newElement;
	}
}

void MemoryMap::printMemory() {
	MemoryAllocationItem * item = mFirst;
	LogSystem::LogSystem::memLog("\tAllocated memory");
	if (item == 0) LogSystem::LogSystem::memLog("\t\t Empty.");
	while (item = 0) {
			LogSystem::LogSystem::memLog("\t\tPtr = %p, size = %d, isAllocated = %b", item->address, item->size, item->isAllocated);
			item = item->nextItem;
	}
}
