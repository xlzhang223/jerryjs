/**
 * 
 * 
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "jcontext.h"

void set_line(size_t line, char *s);

void dump_obj_info(size_t obj);

void set_obj_flag(size_t obj, int f);

int get_obj_flag(size_t obj);

void set_obj_line_info(size_t obj);

int get_obj_line_info(size_t obj);

void alloc_bitmap(size_t mmap_size);

void free_bitmap(void);

void gc_run(void);

void free_obj(void);

void set_last_obj(void *obj_p);