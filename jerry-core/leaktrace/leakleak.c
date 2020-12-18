#include "leakleak.h"
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

__uint8_t *bit_p;

const unsigned KB = 1024;

void *last_obj_p;

int debug_obj = 0;

size_t debug_gc = 0;

#define byte char
#define LOG 3
#define LOG2 7
#define DEV 0
#define TIM 2

size_t sed;

struct info
{
    __uint8_t flag : 1;
    __uint8_t info_hash : (1 << LOG) - 1;
};

struct _color
{
    size_t count;
    size_t line;
    char *s;
} color[1 << LOG2];

struct info *mmap_p = NULL;

size_t _line;

char *_s;

FILE *fp = NULL;

void set_line(size_t line, char *s)
{
    _line = line;
    _s = s;
}

//JsObjecTracer
void set_obj_flag(size_t obj, int f)
{
    if (f == 0 && (debug_gc % TIM != 0))
    {
        return;
    }
    // printf("set_obj_flag %d %d\n", obj, f);
#if ENABLED(DEV)
    printf("set_obj_flag %d %d\n", obj, f);
#endif
    // if(offset > rt->mmap_size) return;
    mmap_p[obj].flag = f;
}

void set_obj_line_info(size_t obj)
{
#if ENABLED(DEV)
    printf("set_obj_line_info %d and line %d\n", obj, _line);
#endif
    // printf("set_obj_line_info %d and line %d\n", obj, _line);
    mmap_p[obj].info_hash = ((_line * sed)  * 131) % (1 << LOG2 );
    color[mmap_p[obj].info_hash].s = _s;
    color[mmap_p[obj].info_hash].line = _line;
    // color[_line % (1<<((1<<LOG)-1))].count++;
}

int get_obj_flag(size_t obj)
{
    if (debug_gc % TIM != 0)
        return 1;
// uint32_t offset = (((uintptr_t)obj - (uintptr_t)rt->heap_start ) >> LOG);
// if(offset > rt->mmap_size) return -1;
#if ENABLED(DEV)
    printf("get_obj_flag %d\n", obj);
#endif
    return mmap_p[obj].flag;
}

int get_obj_line_info(size_t obj)
{
// uint32_t offset = (((uintptr_t)obj - (uintptr_t)rt->heap_start ) >> LOG);
#if ENABLED(DEV)
    printf("get_obj_line_info %d\n", obj);
#endif
    // if(offset > rt->mmap_size) return -1;
    return mmap_p[obj].info_hash;
}

void dump_obj_info(size_t obj)
{
    if (mmap_p[obj].info_hash != 0)
    {
        color[mmap_p[obj].info_hash].count = 1;
#if ENABLED(DEV)
        printf("maybe leak obj:%x %d line info:%d\n", add, obj, mmap_p[obj].info_hash);
#endif
    }
}

void alloc_bitmap(size_t mmap_size)
{
    srand(time(0));
    sed = rand();
    fp = fopen("result.txt", "a");
#if ENABLED(DEV)
    printf("alloc_bitmap mmap_size%d\n");
#endif
    mmap_p = (struct info *)mmap(NULL, mmap_size, PROT_READ | \
     PROT_WRITE, MAP_PRIVATE | \
     MAP_ANONYMOUS, -1, 0);
}

void free_bitmap(void)
{
    for (int i = 0; i < (1 << LOG2); i++)
    {
        if (color[i].count != 0)
        {
            
            // fprintf(fp, "color[%d] count:%d from:%s\n", i, color[i].count, color[i].s);
            int j = 0;
            fprintf(fp,"color[ %d ] line: %d from: ", i, color[i].line);
            while (color[i].s[j] > 0)
            {
                fprintf(fp,"%c",color[i].s[j++]);
                /* code */
            }
            fprintf(fp, "\n");

            
            j = 0;
            printf("color[ %d ] line: %d from: ", i, color[i].line);
            while (color[i].s[j] > 0)
            {
                printf("%c",color[i].s[j++]);
                /* code */
            }
            printf("\n");
        }
        else
        {
            if (color[i].line != 0)
            {
                
                // fprintf(fp, "color[%d] count:%d from:%s\n", i, color[i].count, color[i].s);
                int j = 0;
                fprintf(fp,"no_color[ %d ] line: %d from: ", i, color[i].line);
                while (color[i].s[j] > 0)
                {
                    fprintf(fp,"%c",color[i].s[j++]);
                    /* code */
                }
                fprintf(fp, "\n");

                
                j = 0;
                printf("no_color[ %d ] line: %d from: ", i, color[i].line);
                while (color[i].s[j] > 0)
                {
                    printf("%c",color[i].s[j++]);
                    /* code */
                }
                printf("\n");
            }
        }
        
    }

    fclose(fp);
    
#if ENABLED(DEV)
    printf("JsObjecTracer free bitmap \n");
#endif
    // free(bit_p);
}

void gc_run(void)
{
    debug_gc++;
#if ENABLED(DEV)
    printf("JsObjecTracer gc_run %d\n", debug_gc);
#endif
}

void free_obj(void)
{
#if ENABLED(DEV)
    printf("JsObjecTracer free_obj \n");
#endif
}

void set_last_obj(void *obj_p)
{
    last_obj_p = obj_p;
}