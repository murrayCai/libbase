#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <base.h>

int lfree(void *data){
    free(data);
    return 0;
}

int lfor(void *data,uint index){
    kv_t *d = (kv_t *)data;
    printf("[%d]\tkey=%s\tval=%s\n",index,d->key,d->val);
    return 0;
}

int main(int argc,char *argv[]){
    list_t *l = NULL;
    l = list_init(lfree); 
    mem_show();

    kv_t *kv = malloc(sizeof(kv_t));
    memset(kv,0,sizeof(kv_t));
    kv->key = "key";
    kv->val = "val";

    assert(0 == list_add(l,kv));
    assert(1 == l->size);
    kv_t *d = list_index(l,0);
    assert(NULL != d);
    
    // printf("%p\t%p\t%s\t%s\n",d,kv,d->key,d->val);
    
    assert(kv == list_index(l,0));

    list_for(l,lfor);

    list_free(l);
    return 0;
}
