#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define M_ARR(expr) M((expr),MODULE_ARR)

int arr_init(arr_t **pptr,uint count){
    M_ARR(NULL == pptr);

    M_ARR(0 >= count);
    R(MALLOC_T(pptr,arr_t));

    ptr_t *data = NULL;

    RC(MALLOC_TN(&data,ptr_t,count),({
        FREE_T(pptr,arr_t);
    }));

    (*pptr)->data = data;
    (*pptr)->count = count;
    return 0;
}

int arr_free(arr_t **pp){
    M_ARR(NULL == pp);
    M_ARR(NULL == *pp);

    arr_t *arr = *pp;
    if(NULL != arr->data){
        R(FREE_TN(&(arr->data),ptr_t,arr->count));
    }
    R(FREE_T(pp,arr_t));
    return 0;
}

int arr_add(arr_t *arr,void *data){
    M_ARR(NULL == arr);
    M_ARR(NULL == data);

    if(arr->used >= arr->count){
        ptr_t *d = NULL;
        R(MALLOC_TN(&d,ptr_t,arr->count * 2));
        memcpy(d,arr->data,arr->count * sizeof(ptr_t));
        R(FREE_TN(&(arr->data),ptr_t,arr->count));
        arr->count *= 2;
        arr->data = d;
    }

    arr->data[arr->used++] = data;
    return 0;
}

int arr_index(void **dst,arr_t *arr,uint index){
    M_ARR(NULL == arr);
    M_ARR(NULL == dst);
    M_ARR(0 > index || index >= arr->used);
    *dst = arr->data[index];
    return 0;
}
