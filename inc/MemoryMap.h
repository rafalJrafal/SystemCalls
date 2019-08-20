#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cstdlib>

struct MemoryAllocation {
	MemoryAllocation() : address(0), size(0), isAllocated(true) {
	}
	void * address;
	size_t size;
	bool isAllocated;
};

struct MemoryAllocationItem : public MemoryAllocation {
	MemoryAllocationItem(MemoryAllocation & e) {
		address = e.address;
		size = e.size;
		isAllocated = e.isAllocated;
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
		void setPrintDeallocations(bool b) {
			mPrintDeallocations = b;
		}
		
	private:
		void addMemoryItem(MemoryAllocationItem);
		void markMemoryItemFree(void * ptr);
		void printMemory();
		MemoryAllocationItem * mFirst;
		
		int mAllocationNumber;
		int mDeallocationNumber;
		
		bool mPrintAllocations, mPrintDeallocations;
};

#endif
