#include "../inc/Memory.h"

void * operator new(size_t size) {
	void * m = malloc(size);
	return m;
}
void operator delete(void * p) {
	free(p);
}

