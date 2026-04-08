#ifndef MEMORY_H
#define MEMORY_H

#define MEM_API

#if defined(DLLBLD)
#if defined (_WIN32) || defined (_WIN64)
#define MEM_API __declspec(dllexport)
#endif
#endif

#if defined (USEDLL)
#if defined (_WIN32) || defined (_WIN64)
#define MEM_API __declspec(dllexport)
#endif
#endif

#define IS_FREE         0b00000001
#define IS_USING        0b00000010

typedef unsigned long long size_t;

MEM_API void* cmalloc(size_t size);
MEM_API void cfree(void *block); //free with merge
MEM_API void* crealloc(void *block, size_t size);
MEM_API void memcpy_av(void *restrict dst, void *restrict src, const unsigned long size);

#endif