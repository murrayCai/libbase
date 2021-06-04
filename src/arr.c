#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mc.h"

#ifdef MODULE_CURR
#undef MODULE_CURR
#define MODULE_CURR MODULE_ARR
#endif

int arr_init(arr_t **pptr,uint count){
    int ret = 0;
    R(NULL == pptr);
    R(NULL != *pptr);

    R(0 >= count);
    R(MALLOC_T(pptr,arr_t));

    ptr_t *data = NULL;

    RC(MALLOC_TN(&data,ptr_t,count),({
                FREE_T(pptr,arr_t);
                }));

    (*pptr)->data = data;
    (*pptr)->count = count;
    return 0;
}

int arr_add_with_type_data(void **dist,arr_t *arr,size_t size,mi_e index,const char *name){
    int ret = 0;
    R(NULL == dist);
    R(NULL != (*dist));
    R(NULL == arr);
    R(0 >= size);
    R(MI_CHECK(index));
    R(NULL == name);

    R(malloc_t(dist,size,index,name));
    R(arr_add(arr,(*dist)));

    return ret;
}

int arr_free_with_type_data(arr_t **pp,size_t size,mi_e index){
    int ret = 0;
    int j = 0;
    void *ptr = NULL;
    R( NULL == pp );
    R( NULL == (*pp) );
    R(0 >= size);
    R(MI_CHECK(index));

    for(; j < (*pp)->used; j++){
        ptr = NULL;
        R(arr_index(&ptr,(*pp),j));
        R(free_t(&ptr,size,index));
    }
    R(arr_free(pp));
    return ret;
}


int arr_init_with_type_data(arr_t **pp,uint count,size_t size,mi_e index,const char *name){
    int ret = 0,errRet = 0;
    void *ptr = NULL;
    int i = 0;
    R(NULL == pp);
    R(NULL != *pp);
    R(0 >= count);
    R(0 >= size);
    R(MI_CHECK(index));
    R(NULL == name);

    R(arr_init(pp,count));
    for(; i < count; i++){
        ptr = NULL;
        G_E(malloc_t(&ptr,size,index,name));
        G_E( arr_add( (*pp), ptr ) );
    }
    return ret;

error:
    errRet = ret;
    R(arr_free_with_type_data(pp,size,index));
    return errRet;
}

int arr_free(arr_t **pp){
    int ret = 0;
    R(NULL == pp);
    R(NULL == *pp);

    arr_t *arr = *pp;
    if(NULL != arr->data){
        R(FREE_TN(&(arr->data),ptr_t,arr->count));
    }
    R(FREE_T(pp,arr_t));
    return 0;
}

static int _arr_resize(arr_t *arr){
    int ret = 0;
    if(arr->used >= arr->count){
        R(REALLOC_TN(&(arr->data),ptr_t,&(arr->count)));
    }
    return ret;
}

int arr_shift(arr_t *arr,void *data){
    int ret = 0;
    R(NULL == arr);
    R(NULL == data);
    R(_arr_resize(arr));
    memcpy(arr->data + 1, arr->data, sizeof(ptr_t) * arr->used );
    arr->data[0] = data;
    arr->used++;
    return ret;
}

int arr_add(arr_t *arr,void *data){
    int ret = 0;
    R(NULL == arr);
    R(NULL == data);

    R(_arr_resize(arr));

    arr->data[arr->used++] = data;
    return 0;
}

int arr_index(void **dst,arr_t *arr,uint index){
    int ret = 0;
    R(NULL == arr);
    R(NULL == dst);
    R(0 > index || index >= arr->used);
    *dst = arr->data[index];
    return 0;
}

int arr_delete_index(arr_t *arr,uint index){
    int ret = 0;
    R(NULL == arr);
    R(0 > index || index >= arr->used);
    arr->data[index--] = NULL;
    arr->used--;
    return ret;
}

int arr_delete_index_then_resort(arr_t *arr,uint index){
    int ret = 0;
    R(NULL == arr);
    R(arr->used - 1 < index);
    R(arr_delete_index(arr,index));
    int afterItemCount = arr->used - index;
    if(afterItemCount > 0){
        memcpy(arr->data + index,arr->data + index + 1,afterItemCount * sizeof(ptr_t));
        arr->data[arr->used + 1] = NULL;
    }
    return ret;
}

int arr_foreach(arr_t *arr,uint start,cb_arr_foreach f){
    int ret = 0;
    R(NULL == arr);
    R(0 > start);
    R(start >= arr->used);
    if(NULL != f){
        for(;start < arr->used; start++){
            R(f(start,arr->data[start]));
        }
    }
    return ret;
}
