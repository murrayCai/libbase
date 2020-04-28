#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/base.h"

int main(int argc,char *argv[]){
    
    char *str = NULL;
    CC(MALLOC_S(&str,64));
    assert(NULL != str);

    FREE_S(&str,64);
    assert(NULL == str);

    list_t *list = NULL;
    CC(MALLOC_T(&list,list_t));
    assert(NULL != list);

    FREE_T(&list,list_t);
    assert(NULL == list);;

    mem_show();

    return 0;
}
