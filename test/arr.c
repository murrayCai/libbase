#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "base.h"

int main(int argc,char *argv[]){
    arr_t *arr = arr_init(4);
    assert(NULL != arr);
    assert(4 == arr->count);
    mem_show();

    arr_add(arr,"test1");
    arr_add(arr,"test2");
    arr_add(arr,"test3");
    arr_add(arr,"test4");
    assert(4 == arr->used);
    assert("test4" == arr->data[3]);

    mem_show();

    arr_add(arr,"test5");
    mem_show();
    assert(8 == arr->count);
    assert(5 == arr->used);
    assert("test5" == arr->data[4]);
    assert("test1" == arr_index(arr,0));
    assert("test2" == arr_index(arr,1));
    assert("test3" == arr_index(arr,2));

    arr_free(arr);
    mem_show();
    return 0;
}
