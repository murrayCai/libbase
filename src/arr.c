#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"


arr_t *arr_init(uint count){
    arr_t *arr = MALLOC_T(arr_t);
    RETURN_NULL_IF_FAIL(NULL!=arr);

    ptr_t *data = MALLOC_TN(ptr_t,count);
    if(NULL == data){
        FREE_T(arr,arr_t);
        return NULL;
    }
    arr->data = data;
    arr->count = count;
    return arr;
}

void arr_free(arr_t *arr){
    CHECK_PARAM_VOID(NULL!=arr);
    if(NULL!=arr->data){
        FREE_TN(arr->data,ptr_t,arr->count);
    }
    FREE_T(arr,arr_t);
}

int arr_add(arr_t *arr,void *data){
    CHECK_PARAM(NULL != arr);
    CHECK_PARAM(NULL != data);

    if(arr->used >= arr->count){
        ptr_t *d = MALLOC_TN(ptr_t,arr->count * 2);
        RETURN_VAL_IF_FAIL(NULL!=d,ERR_MALLOC_NULL);
        memcpy(d,arr->data,arr->count * sizeof(ptr_t));
        FREE_TN(arr->data,ptr_t,arr->count);
        arr->count *= 2;
        arr->data = d;
    }

    arr->data[arr->used++] = data;
    return 0;
}

void *arr_index(arr_t *arr,uint index){
    CHECK_PARAM_NULL(index < arr->used);
    return arr->data[index];
}
