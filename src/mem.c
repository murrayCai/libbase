#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "base.h"

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

int mem_init(){
    assert(MI_MAX > 1);
    size_t size = sizeof(mem_item_t) * MI_MAX;
    mItems = (mem_item_t *)MALLOC(size);
    RETURN_VAL_IF_FAIL(NULL!=mItems,ERR_MALLOC_NULL);
    memset(mItems, 0 , size);
    mItems[0].name = "mem_item_t";
    mItems[0].used = size;
    mItems[0].mCount = 1;
    mItems[0].fCount = 0;
    mItems[0].mTotal = size;
    return 0;
}

void mem_show(){
    RETURN_IF_CHECK_FAIL(NULL!=mItems);
    int i = 0;
    // name used(mCount/fCount) total
    const char *fmt = "%s\t%u(%u/%u)\t%u\n";
    printf("\n=================MEM USAGE===============\n");
    printf("NAME\tUSED(mCount/fCount)\ttotal\n");
    for(;i<MI_MAX;i++){
        printf(fmt,mItems[i].name,mItems[i].used,mItems[i].mCount,
                mItems[i].fCount,mItems[i].mTotal);
    }
    printf("=================   END   ===============\n\n");
}

void mem_finish(){
    if(NULL!=mItems){
        free(mItems);
        mItems = NULL;
    } 
}

void *malloc_t(size_t size,mi_e index,const char *name){
    if(NULL==mItems) mem_init();
    RETURN_NULL_IF_CHECK_FAIL(index > 0 && index < MI_MAX);
    void *d = MALLOC(size);
    RETURN_NULL_IF_FAIL(NULL!=d);
    mItems[index].name = name;
    mItems[index].mCount++;
    mItems[index].mTotal+=size;
    mItems[index].used+=size;
    mItems[0].mCount++;
    mItems[0].used+=size;
    mItems[0].mTotal+=size;
    return d;
}

void *malloc_tn(size_t count,size_t size,mi_e index,const char *name){
    if(NULL==mItems) mem_init();
    RETURN_NULL_IF_CHECK_FAIL(index > 0 && index < MI_MAX);
    size_t total = size * count;
    void *d = MALLOC(total);
    RETURN_NULL_IF_FAIL(NULL!=d);
    mItems[index].name = name;
    mItems[index].mCount++;
    mItems[index].mTotal+=total;
    mItems[index].used+=total;
    mItems[0].mCount++;
    mItems[0].used+=total;
    mItems[0].mTotal+=total;
    return d;

}

void free_t(void *ptr,size_t size,mi_e index){
    if(NULL != ptr){
        free(ptr);
        mItems[index].fCount++;
        mItems[index].used-=size;
        mItems[0].fCount++;
        mItems[0].used-=size;
        ptr = NULL;
    }
}

void free_tn(void *ptr,size_t count,size_t size,mi_e index){
    if(NULL != ptr){
        free(ptr);
        uint total = size * count;
        mItems[index].fCount++;
        mItems[index].used -= total ;
        mItems[0].fCount++;
        mItems[0].used -= total;
        ptr = NULL;
    }
}
