#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define C_ARR_PARAM(expr) CHECK_PARAM((expr),MODULE_ARR)

int arr_init(arr_t **pptr,uint count){
    C_ARR_PARAM(NULL != pptr);

    C_ARR_PARAM(0 < count);
    CC(MALLOC_T(pptr,arr_t));

    ptr_t *data = NULL;

    CCB(MALLOC_TN(&data,ptr_t,count),({
        FREE_T(pptr,arr_t);
    }));

    (*pptr)->data = data;
    (*pptr)->count = count;
    return 0;
}

int arr_free(arr_t **pp){
    C_ARR_PARAM(NULL != pp);
    C_ARR_PARAM(NULL != *pp);

    arr_t *arr = *pp;
    if(NULL != arr->data){
        CC(FREE_TN(&(arr->data),ptr_t,arr->count));
    }
    CC(FREE_T(pp,arr_t));
    return 0;
}

int arr_add(arr_t *arr,void *data){
    C_ARR_PARAM(NULL != arr);
    C_ARR_PARAM(NULL != data);

    if(arr->used >= arr->count){
        ptr_t *d = NULL;
        CC(MALLOC_TN(&d,ptr_t,arr->count * 2));
        memcpy(d,arr->data,arr->count * sizeof(ptr_t));
        CC(FREE_TN(&(arr->data),ptr_t,arr->count));
        arr->count *= 2;
        arr->data = d;
    }

    arr->data[arr->used++] = data;
    return 0;
}

int arr_index(void **dst,arr_t *arr,uint index){
    C_ARR_PARAM(NULL != arr);
    C_ARR_PARAM(NULL != dst);
    C_ARR_PARAM(index < arr->used);
    *dst = arr->data[index];
    return 0;
}
