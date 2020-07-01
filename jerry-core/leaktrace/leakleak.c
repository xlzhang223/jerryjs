#include "leakleak.h"

__uint8_t* bit_p;
const unsigned KB = 1024;
void* last_obj_p;
void dump_obj_info(void){
    printf("zhang you can build \n");
}

void alloc_bitmap(void){
    printf("zhang alloc bitmap \n");
    bit_p = (__uint8_t*)malloc((unsigned)64*KB);
    const void* heap_start = (void*) &JERRY_HEAP_CONTEXT (first);
    printf("zhang heap_start %#x \n",heap_start);
}

void free_bitmap(void){
    printf("zhang free bitmap \n");
    printf("zhang leak obj %#x and line: 4 \n",last_obj_p);
    free(bit_p);
}

void gc_run(void){
    printf("zhang gc_run \n");
}

void free_obj(void){
    printf("zhang free_obj \n");
}

void set_last_obj(void* obj_p){

    last_obj_p = obj_p;
}