#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cstdlib>

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
