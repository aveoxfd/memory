#include <memoryapi.h>
#include <stdio.h>
#define NONE 0
#define MESSAGE 0x10000000
#define ERROR   0x20000000

#define FIRST_INIT 0x1
#define CANNOT_FIND_ADDRESS 0x1

#define FREE 0b00000000000000000000000000000001

typedef struct block_headerer{
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

block_header *find_free_block(size_t size){
    block_header *current = general.list;

    while(current){
        if (current->flag & FREE && size <= current->size) return current;
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

    

    
    return out;
}

void cfree(void *__address){
    return;
}

int main(){
    printf("0x%0x\n", cmalloc(NULL, 2));
    printf("0x%0x\n", cmalloc(NULL, 10));
    printf("0x%0x\n", general.list[0]);
    return 0;
}