#include <memoryapi.h>
#include <stdio.h>
#include "memory.h"

typedef long align;

typedef struct block_header{
    void *address; //virtual address
    size_t size;
    int flag;
    struct block_header *next;
}block_header, block_header_t;

typedef struct GENMNG{
    block_header *list; //list of free blocks
    //TODO: functions, that works with GENMNG
}GENMNG;

//static block_header_t* list = NULL;
static GENMNG general = {NULL};

block_header *find_free_block(size_t size){ //this function returns the first suitable block which will be split if the desired size is smaller than block size
    block_header *current = general.list;

    while(current){
        if (size <= current->size){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void* cmalloc(void *desired_address, size_t size){
    void * out;

    if (general.list == NULL){
        printf("List of headers is NULL. Inititalizating.\n");
        void *start;
        do{
            start = VirtualAlloc(NULL, sizeof(block_header_t*), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        }while(start == NULL);

        block_header *first = (block_header_t*)start;
        first->address = start;
        first->size = size;
        first->flag = NONE;
        first->next = NULL;

        general.list = first;
        return NULL;
    }

    block_header_t *founded_block = find_free_block(size);
    founded_block->size = founded_block->size - size;
    

    
    return out;
}

void cfree(void *__address){
    return;
}