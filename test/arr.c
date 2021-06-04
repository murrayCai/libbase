#include <assert.h>
#include "mc.h"

int main(int argc,char *argv[]){
    int ret = 0;
    arr_t *arr = NULL;
    RL(arr_init(&arr,4),"malloc failed!\n");
    E(NULL == arr);
    E(4 != arr->count);

    arr_add(arr,"test1");
    arr_add(arr,"test2");
    arr_add(arr,"test3");
    arr_add(arr,"test4");
    E(4 != arr->used);
    E(strcmp("test4",arr->data[3]));

    arr_add(arr,"test5");
    E(8 != arr->count);
    E(5 != arr->used);
    E(strcmp("test5",arr->data[4]));
    
    char *str = NULL;
    RL(arr_index((void **)&str,arr,0),"arr_index failed!\n");
    E(strcmp("test1",str));
    
    RL(arr_index((void **)&str,arr,1),"arr_index failed!\n");
    E(strcmp("test2",str));
    
    RL(arr_index((void **)&str,arr,2),"arr_index failed!\n");
    E(strcmp("test3", str));

    printf("compile success\n");

    RL(arr_free(&arr),"arr_free failed!");
    E(NULL != arr);
    mem_show();
    return 0;
}
