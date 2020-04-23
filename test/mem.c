#include <stdio.h>
#include <stdlib.h>
#include "../src/base.h"

int main(int argc,char *argv[]){
    mem_init();
    mem_show();
    
    char *str = MALLOC_S(64);
    mem_show();

    FREE_S(str,64);
    mem_show();

    list_t *list = NULL;
    list = MALLOC_T(list_t);
    mem_show();

    FREE_T(list,list_t);
    mem_show();

    mem_finish();
    mem_show();

    return 0;
}
