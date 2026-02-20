gcc -D MEMORY_STATIC -c src/memory.c -o obj/memory.o -Isrc
ar rcs lib/libmemory.a obj/memory.o

ar t lib/libmemory.a
nm lib/libmemory.a