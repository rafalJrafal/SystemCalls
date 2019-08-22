#include "../inc/MemoryMap.h"
#include "../../LogSystem/inc/LogSystem.h"

MemoryMap& MemoryMap::instance() {
	static MemoryMap memoryMap;
	return memoryMap;
}

MemoryMap::MemoryMap() : mFirst(0), mAllocationNumber(0), mDeallocationNumber(0), mPrintAllocations(true), 
	mPrintOtherDeallocations(true), mPrintSelfDeallocations(true) {
	
}

MemoryMap::MemoryMap(MemoryMap&) {
	
}

void MemoryMap::markAlloc(void * ptr, size_t size) {
	if (mPrintAllocations) LogSystem::LogSystem::memLog("MarkAlloc:\t\tptr = %p\t\tsize = %d.", ptr, size);
	struct MemoryAllocation mem;
	mem.address = ptr;
	mem.size = size;
	mem.isAllocated = true;
	mAllocationNumber++;
	addMemoryItem(MemoryAllocationItem(mem));
	if (mPrintAllocations) printMemory();
}

void MemoryMap::markAlloc(void * ptr, size_t size, const char * file, int line) {
	if (mPrintAllocations) LogSystem::LogSystem::memLog("MarkAlloc:\t\tptr = %p\t\tsize = %d. %s : %d", ptr, size, file, line);
	struct MemoryAllocation mem;
	mem.address = ptr;
	mem.size = size;
	mem.isAllocated = true;
	mem.size = size;
	strcpy(mem.fileName, file);
	mem.line = line;
	mAllocationNumber++;
	addMemoryItem(MemoryAllocationItem(mem));
	if (mPrintAllocations) printMemory();
	
}

void MemoryMap::markFree(void * ptr) {
	bool foundItemToFree = false;

	MemoryAllocationItem * item = mFirst;
	while (item != 0) {
			if (item->isAllocated == true && item->address == ptr) {
				foundItemToFree = true;
				break;
			}
			item = item->nextItem;
	}
	if (foundItemToFree) {
		if (mPrintSelfDeallocations) LogSystem::LogSystem::memLog("Deallocated memory at\tptr = %p. File %s : %d", 
			ptr, item->fileName, item->line);
		mDeallocationNumber++;
		markMemoryItemFree(ptr);
		if (mPrintSelfDeallocations) printMemory();
	}
	else {
		if (mPrintOtherDeallocations) LogSystem::LogSystem::memLog("\t\t\t\tFound deallocated memory at\tptr = %p", ptr);
	}
}

void MemoryMap::addMemoryItem(MemoryAllocationItem item) {
	if (mFirst == 0) {
		mFirst = (MemoryAllocationItem*)malloc(sizeof(MemoryAllocationItem));
		mFirst->address = item.address;
		mFirst->size = item.size;
		mFirst->isAllocated = item.isAllocated;
		strcpy(mFirst->fileName, item.fileName);
		mFirst->line = item.line;
		mFirst->nextItem = 0;
	}
	else {
		MemoryAllocationItem * newElement = (MemoryAllocationItem*)malloc(sizeof(MemoryAllocationItem));
		newElement->address = item.address;
		newElement->size = item.size;
		newElement->isAllocated = item.isAllocated;
		newElement->nextItem = 0;
		strcpy(newElement->fileName, item.fileName);
		newElement->line = item.line;
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
			LogSystem::LogSystem::memLog("\tPtr = %p,\tsize = %d, \t isAllocated = %d. File: %s : %d All Size Used = %d", 
				item->address, item->size, item->isAllocated, item->fileName, item->line, (int)sizeUsed);
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
				LogSystem::LogSystem::memLog("\t\tPtr = %p,\tsize = %d,\tisAllocated = %d from file %s : %d", 
					item->address, item->size, item->isAllocated, item->fileName, item->line);
				count++;
				remainingSize += item->size;
			}
			item = item->nextItem;
	}
	LogSystem::LogSystem::memLog("Number of remaining allocations = %d", count, remainingSize);
	LogSystem::LogSystem::memLog("\n==================================================");
}
