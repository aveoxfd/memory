gcc -shared -o lib/memory.dll src/memory.c -D DLLBLD

gcc -c src/memory.c -o obj/memory.o
ar rc lib/memory.lib obj/memory.o

nm lib/memory.lib