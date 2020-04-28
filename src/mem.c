#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "base.h"

#define C_MEM(exp,code) _CHECK((exp),code,MODULE_MEM)
#define C_MEM_MALLOC(ptr) CHECK_MALLOC((ptr),MODULE_MEM)
#define C_MEM_PARAM(exp) CHECK_PARAM((exp),MODULE_MEM) 

#define MALLOC(ptr,size) \
    do{\
        (ptr) = malloc(size);\
        C_MEM_MALLOC(ptr);\
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
    C_MEM_PARAM(NULL!=mItems);
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
    C_MEM_PARAM(NULL != pptr);
    C_MEM_PARAM(NULL != name);
    C_MEM_PARAM(0 < size);
    C_MEM_PARAM(index > 0 && index < MI_MAX);

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
    C_MEM_PARAM(NULL != pptr);
    C_MEM_PARAM(NULL != name);
    C_MEM_PARAM(0 < size);
    C_MEM_PARAM(0 < count);
    C_MEM_PARAM(index > 0 && index < MI_MAX);
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
    C_MEM_PARAM(NULL != pptr);
    C_MEM_PARAM(0 < size);
    C_MEM_PARAM(index > 0 && index < MI_MAX);
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
    C_MEM_PARAM(NULL != pptr);
    C_MEM_PARAM(0 < size);
    C_MEM_PARAM(0 < count);
    C_MEM_PARAM(index > 0 && index < MI_MAX);
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
