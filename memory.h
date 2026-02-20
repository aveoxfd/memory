#ifndef MEMORY_H
#define MEMORY_H

#define FREE        0b00000001
#define IS_USING    0b00000010

typedef unsigned long long size_t;

void* cmalloc(size_t size);
void cfree(void *block);

#endif