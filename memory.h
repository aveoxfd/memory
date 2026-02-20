#ifndef MEMORY_H
#define MEMORY_H

#define NONE 0
#define MESSAGE 0x10000000
#define ERROR   0x20000000

#define FIRST_INIT 0x1
#define CANNOT_FIND_ADDRESS 0x1

#define FREE        0b00000001
#define IS_USING    0b00000010

typedef unsigned long long size_t;

void* cmalloc(size_t size);
void cfree(void *__address);

#endif