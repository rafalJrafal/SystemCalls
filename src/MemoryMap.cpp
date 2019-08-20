#include "../inc/MemoryMap.h"
#include "../../LogSystem/inc/LogSystem.h"

MemoryMap& MemoryMap::instance() {
	static MemoryMap memoryMap;
	return memoryMap;
}

MemoryMap::MemoryMap() : mFirst(0), mAllocationNumber(0), mDeallocationNumber(0), mPrintAllocations(true), mPrintDeallocations(true) {
	
}

MemoryMap::MemoryMap(MemoryMap&) {
	
}

void MemoryMap::markAlloc(void * ptr, size_t size) {
	if (mPrintAllocations) LogSystem::LogSystem::memLog("Allocated memory at\tptr = %p\tsize = %d.", ptr, size);
	struct MemoryAllocation mem;
	mem.address = ptr;
	mem.size = size;
	mem.isAllocated = true;
	mAllocationNumber++;
	addMemoryItem(MemoryAllocationItem(mem));
	if (mPrintAllocations) printMemory();
}

void MemoryMap::markAlloc(void * ptr, size_t size, const char * file, int line) {
	if (mPrintAllocations) LogSystem::LogSystem::memLog("Allocated memory at\tptr = %p\tsize = %d. From %s : %d", ptr, size, file, line);
	struct MemoryAllocation mem;
	mem.address = ptr;
	mem.size = size;
	mem.isAllocated = true;
	mem.size = size;
	mAllocationNumber++;
	addMemoryItem(MemoryAllocationItem(mem));
	if (mPrintAllocations) printMemory();
	
}

void MemoryMap::markFree(void * ptr) {
	if (mPrintDeallocations) LogSystem::LogSystem::memLog("\t\t\t\tDeallocated memory at\tptr = %p", ptr);
	mDeallocationNumber++;
	markMemoryItemFree(ptr);
	if (mPrintDeallocations) printMemory();
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

void MemoryMap::markMemoryItemFree(void * ptr) {
	MemoryAllocationItem * item = mFirst;
	while (item != 0) {
			if (item->isAllocated == true && item->address == ptr) {
				item->isAllocated = false;
				LogSystem::LogSystem::memLog("\tDeallocated memory size = %d", item->size);
				return;
			}
			item = item->nextItem;
	}
} 

void MemoryMap::printMemory() {
	MemoryAllocationItem * item = mFirst;
	LogSystem::LogSystem::memLog("\tAllocated memory");
	if (item == 0) LogSystem::LogSystem::memLog("\t\t Empty.");
	size_t sizeUsed = 0;
	while (item != 0) {
			if (item->isAllocated) {
				sizeUsed += item->size;
			}
			LogSystem::LogSystem::memLog("\t\tPtr = %p,\tsize = %d, \tisAllocated = %d.\tAll Size Used = %d", 
				item->address, item->size, item->isAllocated, sizeUsed);
			item = item->nextItem;
	}
	LogSystem::LogSystem::memLog("\tAll size used = %d. Allocations = %d. Deallocations = %d", sizeUsed, mAllocationNumber, mDeallocationNumber);
}

MemoryMap::~MemoryMap() {
	MemoryAllocationItem * item = mFirst;
	while (item != 0) {
			MemoryAllocationItem * toBeRemoved = item;
			item = item->nextItem;
			free(toBeRemoved);
	}
}

void MemoryMap::printRemainingAllocations() {
	MemoryAllocationItem * item = mFirst;
	LogSystem::LogSystem::memLog("\n==================================================");
	LogSystem::LogSystem::memLog("\nRemaining allocations:");
	unsigned long count = 0;
	size_t remainingSize = 0;
	while (item != 0) {
			if (item->isAllocated) {
				LogSystem::LogSystem::memLog("\t\tPtr = %p,\tsize = %d,\tisAllocated = %d.", 
					item->address, item->size, item->isAllocated);
				count++;
				remainingSize += item->size;
			}
			item = item->nextItem;
	}
	LogSystem::LogSystem::memLog("Number of remaining allocations = %d", count, remainingSize);
	LogSystem::LogSystem::memLog("\n==================================================");
}
