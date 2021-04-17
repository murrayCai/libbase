#include <assert.h>
#include "mc.h"

int main(int argc,char *argv[]){
    int ret = 0;
    arr_t *arr = NULL;
    RL(arr_init(&arr,4),"malloc failed!\n");
    assert(NULL != arr);
    assert(4 == arr->count);

    arr_add(arr,"test1");
    arr_add(arr,"test2");
    arr_add(arr,"test3");
    arr_add(arr,"test4");
    assert(4 == arr->used);
    assert("test4" == arr->data[3]);

    arr_add(arr,"test5");
    assert(8 == arr->count);
    assert(5 == arr->used);
    assert("test5" == arr->data[4]);
    char *str = NULL;
    RL(arr_index((void **)&str,arr,0),"arr_index failed!\n");
    assert("test1" == str);
    
    RL(arr_index((void **)&str,arr,1),"arr_index failed!\n");
    assert("test2" == str);
    
    RL(arr_index((void **)&str,arr,2),"arr_index failed!\n");
    assert("test3" == str);

    printf("compile success\n");

    RL(arr_free(&arr),"arr_free failed!");
    assert(NULL == arr);
    mem_show();
    return 0;
}
