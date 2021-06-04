#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mc.h"

#ifdef MODULE_CURR
#undef MODULE_CURR
#define MODULE_CURR MODULE_MEM
#endif


#define MALLOC(ptr,size) \
    do{\
        (ptr) = malloc(size);\
        R(NULL == ptr);\
        memset(ptr,0,size);\
    }while(0)

int mem_show(){
    int ret = 0;
    MC_INIT();
    int i = 0;
    // name used(mCount/fCount) total
    const char *fmt = "%s\t%u(%u/%u)\t%u\n";
    printf("\n=================MEM USAGE===============\n");
    printf("NAME\t\tUSED(mCount/fCount)\ttotal\n");
    for(;i<MI_MAX;i++){
        printf(fmt,mc->mItems[i].name,mc->mItems[i].used,mc->mItems[i].mCount,
                mc->mItems[i].fCount,mc->mItems[i].mTotal);
    }
    printf("=================   END   ===============\n\n");
    return 0;
}

int mem_finish(){
    if(NULL != mc->mItems){
        free(mc->mItems);
        mc->mItems = NULL;
    } 
    return 0;
}

int malloc_t(void **pptr,size_t size,mi_e index,const char *name){
    int ret = 0;
    R(NULL == pptr);
    R(NULL == name);
    R(0 >= size);
    R(MI_CHECK(index));

    MC_INIT();

    MALLOC(*pptr,size);

    mc->mItems[index].name = name;
    mc->mItems[index].mCount++;
    mc->mItems[index].mTotal += size;
    mc->mItems[index].used += size;
    mc->mItems[MI_mem_item_t].mCount++;
    mc->mItems[MI_mem_item_t].used += size;
    mc->mItems[MI_mem_item_t].mTotal += size;

    return 0;
}

int malloc_tn(void **pptr,size_t count,
        size_t size,mi_e index,const char *name)
{
    int ret = 0;
    R(NULL == pptr);
    R(NULL != *pptr);
    R(NULL == name);
    R(0 >= size);
    R(0 >= count);
    R(MI_CHECK(index));
    MC_INIT();

    size_t total = size * count;
    MALLOC(*pptr,total);

    mc->mItems[index].name = name;
    mc->mItems[index].mCount++;
    mc->mItems[index].mTotal+=total;
    mc->mItems[index].used+=total;
    mc->mItems[MI_mem_item_t].mCount++;
    mc->mItems[MI_mem_item_t].used+=total;
    mc->mItems[MI_mem_item_t].mTotal+=total;
    return 0;
}

int realloc_tn(void **pptr,size_t *pCount,
        size_t size,mi_e index,const char *name){
    int ret = 0;
    R(NULL == pptr);
    R(NULL == *pptr);
    R(NULL == name);
    R(0 >= size);
    R(NULL == pCount);
    R(0 >= (*pCount));
    R(MI_CHECK(index));
    MC_INIT();

    size_t newMalloc = size * (*pCount);
    size_t total = size * (*pCount) * 2;
    void * ptr = realloc(*pptr,total);
    R(NULL == ptr);
    *pptr = ptr;
    (*pCount) *= 2;

    mc->mItems[index].name = name;
    mc->mItems[index].rCount++;
    mc->mItems[index].mTotal += newMalloc;
    mc->mItems[index].used += newMalloc;
    mc->mItems[MI_mem_item_t].mCount++;
    mc->mItems[MI_mem_item_t].used += newMalloc;
    mc->mItems[MI_mem_item_t].mTotal += newMalloc;

    return ret;
}

int free_t(void **pptr,size_t size,mi_e index){
    int ret = 0;
    R(NULL == pptr);
    R(0 >= size);
    R(MI_CHECK(index));
    if(NULL != *pptr){
        memset(*pptr,0,size);
        free(*pptr);
        mc->mItems[index].fCount++;
        mc->mItems[index].used-=size;
        mc->mItems[MI_mem_item_t].fCount++;
        mc->mItems[MI_mem_item_t].used-=size;
        *pptr = NULL;
    }
    return 0;
}

int free_tn(void **pptr,size_t count,size_t size,mi_e index){
    int ret = 0;
    R(NULL == pptr);
    R(0 >= size);
    R(0 >= count);
    R(MI_CHECK(index));
    if(NULL != *pptr){
        free(*pptr);
        uint total = size * count;
        mc->mItems[index].fCount++;
        mc->mItems[index].used -= total ;
        mc->mItems[MI_mem_item_t].fCount++;
        mc->mItems[MI_mem_item_t].used -= total;
        *pptr = NULL;
    }
    return 0;
}
