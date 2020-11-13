#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <base.h>

int lfree(void *data){
    free(data);
    return 0;
}

int lfor(void *data,uint index,void **userData){
    kv_t *d = (kv_t *)data;
    printf("[%d]\tkey=%s\tval=%s\n",index,d->key,d->val);
    return 0;
}

int main(int argc,char *argv[]){
    int ret = 0;
    mc_list_t *l = NULL;
    L(mc_list_init(&l,lfree),"list_init failed!\n"); 

    kv_t *kv = NULL;
    L(MALLOC_T(&kv,kv_t),"malloc kv_t failed!\n");
    kv->key = "key";
    kv->val = "val";

    assert(0 == mc_list_add(l,kv));
    assert(1 == l->size);
    kv_t *d = NULL;
    L(mc_list_index((void **)&d,l,0),"list_index failed!\n");
    
    assert(kv == d);

    L(mc_list_for(l,lfor,NULL),"list_for failed!\n");
    L(mc_list_free(&l),"list_free failed!\n");
    L(FREE_T(&kv,kv_t),"free kv_t failed!\n");
    mem_show();
    return 0;
}
