#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "base.h"

#define M_MEM(expr) M((expr),MODULE_MEM)

#define MALLOC(ptr,size) \
    do{\
        (ptr) = malloc(size);\
        M_MEM(NULL == ptr);\
        memset(ptr,0,size);\
    }while(0)

typedef struct mem_item_s mem_item_t;
struct mem_item_s{
    const char *name;
    uint used;
//    uint uCount;
    uint mCount;
    uint fCount;
    uint mTotal;
};

mem_item_t *mItems = NULL;

static int mem_init(){
    int ret = 0;
    assert(MI_MAX > 1);
    size_t size = sizeof(mem_item_t) * MI_MAX;
    MALLOC(mItems,size);
    mItems[0].name = "mem_item_t";
    mItems[0].used = size;
    mItems[0].mCount = 1;
    mItems[0].fCount = 0;
    mItems[0].mTotal = size;
    return 0;
}

int mem_show(){
    int ret = 0;
    M_MEM(NULL == mItems);
    int i = 0;
    // name used(mCount/fCount) total
    const char *fmt = "%s\t%u(%u/%u)\t%u\n";
    printf("\n=================MEM USAGE===============\n");
    printf("NAME\t\tUSED(mCount/fCount)\ttotal\n");
    for(;i<MI_MAX;i++){
        printf(fmt,mItems[i].name,mItems[i].used,mItems[i].mCount,
                mItems[i].fCount,mItems[i].mTotal);
    }
    printf("=================   END   ===============\n\n");
    return 0;
}

int mem_finish(){
    if(NULL != mItems){
        free(mItems);
        mItems = NULL;
    } 
    return 0;
}

int malloc_t(void **pptr,size_t size,mi_e index,const char *name){
    int ret = 0;
    M_MEM(NULL == pptr);
    M_MEM(NULL == name);
    M_MEM(0 >= size);
    M_MI(index,MODULE_MEM);

    if(NULL == mItems) mem_init();

    MALLOC(*pptr,size);

    mItems[index].name = name;
    mItems[index].mCount++;
    mItems[index].mTotal += size;
    mItems[index].used += size;
    mItems[0].mCount++;
    mItems[0].used += size;
    mItems[0].mTotal += size;

    return 0;
}

int malloc_tn(void **pptr,size_t count,
        size_t size,mi_e index,const char *name)
{
    int ret = 0;
    M_MEM(NULL == pptr);
    M_MEM(NULL == name);
    M_MEM(0 >= size);
    M_MEM(0 >= count);
    M_MI(index,MODULE_MEM);

    if(NULL==mItems) mem_init();

    size_t total = size * count;
    MALLOC(*pptr,total);

    mItems[index].name = name;
    mItems[index].mCount++;
    mItems[index].mTotal+=total;
    mItems[index].used+=total;
    mItems[0].mCount++;
    mItems[0].used+=total;
    mItems[0].mTotal+=total;
    return 0;
}

int free_t(void **pptr,size_t size,mi_e index){
    int ret = 0;
    M_MEM(NULL == pptr);
    M_MEM(0 >= size);
    M_MI(index,MODULE_MEM);
    if(NULL != *pptr){
        free(*pptr);
        mItems[index].fCount++;
        mItems[index].used-=size;
        mItems[0].fCount++;
        mItems[0].used-=size;
        *pptr = NULL;
    }
    return 0;
}

int free_tn(void **pptr,size_t count,size_t size,mi_e index){
    int ret = 0;
    M_MEM(NULL == pptr);
    M_MEM(0 >= size);
    M_MEM(0 >= count);
    M_MI(index,MODULE_MEM);
    if(NULL != *pptr){
        free(*pptr);
        uint total = size * count;
        mItems[index].fCount++;
        mItems[index].used -= total ;
        mItems[0].fCount++;
        mItems[0].used -= total;
        *pptr = NULL;
    }
    return 0;
}
