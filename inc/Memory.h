#ifndef MEMORY_H
#define MEMORY_H

#include <cstdlib>

void * operator new(size_t size);
void operator delete(void * p);

#endif
