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

class MemoryMap {
	private:
		MemoryMap();
		MemoryMap(MemoryMap&);
	public:
		static MemoryMap & instance();
		
		void markAlloc(void *, size_t);
		void markFree(void *);
	private:
		
};
#endif
