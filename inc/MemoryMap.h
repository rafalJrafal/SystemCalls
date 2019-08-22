#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cstdlib>
#include <string.h>

struct MemoryAllocation {
	MemoryAllocation() : address(0), size(0), isAllocated(true), line(0) {
		strcpy(fileName, "UNDEFINED");
	}
	void * address;
	size_t size;
	bool isAllocated;
	char fileName[100];
	int line;
};

struct MemoryAllocationItem : public MemoryAllocation {
	MemoryAllocationItem(MemoryAllocation & e) {
		address = e.address;
		size = e.size;
		isAllocated = e.isAllocated;
		strcpy(fileName, e.fileName);
		line = e.line;
	}
	MemoryAllocationItem * nextItem;
};

class MemoryMap {
	private:
		MemoryMap();
		MemoryMap(MemoryMap&);
	public:
		static MemoryMap & instance();
		~MemoryMap();
		
		void markAlloc(void *, size_t);
		void markAlloc(void *, size_t, const char *, int);
		void markFree(void *);
		void printRemainingAllocations();
		
		void setPrintAllocations(bool b) {
			mPrintAllocations = b;
		}
		void setPrintOtherDeallocations(bool b) {
			mPrintOtherDeallocations = b;
		}
		void setPrintSelfDeallocations(bool b) {
			mPrintSelfDeallocations = b;
		}
		
	private:
		void addMemoryItem(MemoryAllocationItem);
		void markMemoryItemFree(void * ptr);
		void printMemory();
		MemoryAllocationItem * mFirst;
		
		int mAllocationNumber;
		int mDeallocationNumber;
		
		bool mPrintAllocations, mPrintOtherDeallocations, mPrintSelfDeallocations;
};

#endif
