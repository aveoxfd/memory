#include <memoryapi.h>
#include <stdio.h>
#include "memory.h"

/*
p[i] = *(p + i)
*/

#define NONE 0
#define MESSAGE 0x10000000
#define ERROR_MSG   0x20000000

#define FIRST_INIT 0x1
#define CANNOT_FIND_ADDRESS 0x1

//typedef long align;

typedef struct block_header{
    size_t size;
    char flag;
    struct block_header *next;
}block_header, block_header_t;

typedef struct GENMNG{
    block_header_t *list; //list of free blocks
    //TODO: functions, that works with GENMNG
}GENMNG;

//static block_header_t* list = NULL;
static GENMNG general = {NULL};

block_header *find_free_block(size_t size){ //this function returns the first suitable block which will be split if the desired size is smaller than block size
    block_header_t *current = general.list;
    while(current){
        if (size <= current->size)return current;
        current = current->next;
    }
    return NULL;
}

void delete_block_from_list(block_header_t *block){
    if (!general.list || !block)return;
    if (general.list == block){
        general.list = block->next;
        return;
    }

    block_header *current = general.list;
    while (current->next && current->next != block)current = current->next;
    if (current->next == block)current->next = block->next;
    else{
        //TODO
    }
    return;
}

MEM_API void* cmalloc(size_t size){
    void *out; //returned address

    if (general.list == NULL){
        printf("General list of headers is NULL. %d\n", sizeof(block_header_t));
        block_header_t* temp = //start list
        (block_header_t*)VirtualAlloc(NULL, sizeof(block_header_t)+size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (temp == NULL){
            printf("No memory. \n");
            return NULL;
        }

        temp->next = NULL;
        temp->size = size;

        out = (char*)temp + sizeof(block_header_t);
        return out;
    }

    //search free space
    block_header_t *free_block = find_free_block(size);

    if (free_block == NULL){ // no memory. size > size of any block in list
        printf("No memory. \n");

        block_header *new_block = VirtualAlloc(NULL, sizeof(block_header_t)+size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (!new_block){
            printf("VirtualAlloc failed.\n");
            return NULL;
        }

        new_block->next = general.list;
        new_block->size = size;
        general.list = new_block;

        free_block = new_block;
    }
    block_header_t *next_from_free_tmp = free_block->next; //temp buffer for next block from free list, because after splitting free_block->next will be changed

    if (size < free_block->size && free_block->size - size > sizeof(block_header_t)){ //spliting
        free_block->next = (block_header_t*)((char*)free_block + sizeof(block_header_t) + size); //address from old block to new

        //free_block->next->size = free_block->size - size;
        block_header_t *new_block = free_block->next;
        new_block->next = next_from_free_tmp;
        new_block->size = free_block->size - size - sizeof(block_header_t);
    }

    if(size==free_block->size){
        //nothing. out = free_block + sizeof(block_header)
    }

    out = (char*)free_block + sizeof(block_header_t);

    delete_block_from_list(free_block);

    return out;
}
void merge(block_header_t* block){
    void* end_block = (void*)((char*)block + sizeof(block_header_t) + block->size);
    block_header_t* current = general.list;

    while (current){
        if (current == block){
            current = current->next;
            continue;
        }
        void* current_end_block = (void*)((char*)current + sizeof(block_header_t) + current->size);

        if ((void*)block == current_end_block){ // part of big another block
            current->size = current->size + sizeof(block_header_t) + block->size;
            delete_block_from_list(block);
            merge(current);
            return;
        }

        if ((void*)end_block == (void*)current){ //size: block += current
            block->size += sizeof(block_header_t) + current->size;
            delete_block_from_list(current);
            merge(block);
            return;
        }
        current = current->next;
    }
    return;
}

MEM_API void cfree(void *block /* = x*/){ //free with merge
    if (!block)return;

    block_header *bl = (block_header_t*)((char*)block - sizeof(block_header));
    //the size parameter has been saved;
    
    bl->next = general.list;
    general.list = bl;

    merge(bl);

    return;
}

MEM_API void crealloc(void *block, size_t size){ // <---- fix
    if (!block || !size)return;

    block_header_t *bl = (block_header_t*)((char*)(block) - sizeof(block_header_t));

    size_t new_size = sizeof(block_header_t) + bl->size + size; //full size of block

    block_header_t *new_block = cmalloc(new_size);

    if (!new_block)return;

    void *new_block_data_ptr = (void*)((char*)new_block + sizeof(block_header_t));

    new_block->next = bl->next;
    new_block -> size = new_size - sizeof(block_header_t);

    for (int i = 0; i < bl->size; i++){
        *((char*)new_block_data_ptr + i) = *((char*)block + i);
    }

    cfree(block);
    block = new_block_data_ptr;
    return;
}