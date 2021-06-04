#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mc.h"

int main(int argc,char *argv[]){
    int ret = 0;
    
    RL_E(mc_init(),"libmc init failed!\n");

    char *str = NULL;
    R(MALLOC_TN(&str,str_t,64));
    assert(NULL != str);

    FREE_TN(&str,str_t,64);
    assert(NULL == str);

    mc_list_t *list = NULL;
    R(MALLOC_T(&list,mc_list_t));
    assert(NULL != list);

    FREE_T(&list,mc_list_t);
    assert(NULL == list);;

    mem_show();

    return 0;
}
