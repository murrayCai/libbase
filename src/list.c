#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define ERR_LIST_ITEM_NOT_FOUND 1
#define M_LIST_VALID(expr) M((expr),MODULE_LIST)

typedef struct mc_list_item_s mc_list_item_t;
struct mc_list_item_s{
    void *data;
    mc_list_item_t *next;
};

int mc_list_free_default(void *data){
    free(data);
    return 0;
}

int mc_list_init(mc_list_t **l,mc_list_free_f f){
    int ret = 0;
    R(MALLOC_T(l,mc_list_t));
    (*l)->free = f;
    return 0;
}

#define _LIST_FREE_ITEM(list,item)\
    do{\
        if(NULL!=(list)->free){ \
            if(0 != (list)->free((item)->data))\
                LOGD("list free function has failed.\n");\
            R(FREE_T(&(item),mc_list_item_t));\
        }else{\
            LOGD("has no defined list free function.\n");\
        }\
    }while(0)

int mc_list_free(mc_list_t **list){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == *list);

    mc_list_t *l = *list;
    mc_list_item_t *curr = (mc_list_item_t *)l->head,*next = NULL;
    while(curr){
        next = curr->next;
        _LIST_FREE_ITEM(l,curr);
        curr = next;
    }

    FREE_T(list,mc_list_t);
    return 0;
}

int mc_list_add(mc_list_t *list,void *data){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == data);

    mc_list_item_t *item = NULL;
    R(MALLOC_T(&item,mc_list_item_t));
    item->data = data;

    if(NULL == list->tail){
        list->head = item;
        list->tail = item;
    }else{
        ((mc_list_item_t *)list->tail)->next = item;
        list->tail = item;
    }

    list->size++;
    return 0;
}

int mc_list_insert(mc_list_t *list,void *data,unsigned int index){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == data);

    mc_list_item_t *item = NULL;
    R(MALLOC_T(&item,mc_list_item_t));
    
    item->data = data;
    if(NULL == list->tail){
        list->head = item;
        list->tail = item;
    }else{

        if(index > list->size - 1){
            ((mc_list_item_t *)list->tail)->next = item;
            list->tail = item;
        }else{
            int i = 0;
            mc_list_item_t *prev = NULL;
            mc_list_item_t *curr = (mc_list_item_t *)list->head;
            while(curr){
                if(i == index){
                    item->next = curr;
                    if(NULL == prev){
                        list->head = item;
                    }else{
                        prev->next = item;
                    }
                }
                i++;
                prev = curr;
                curr = curr->next;
            }
        }
        list->size++;
    }
    return 0;
}

int mc_list_index(void **dst,mc_list_t *list,unsigned int index){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == dst);
    M_LIST_VALID(0 > index || index >= list->size);

    int i = 0,isFound = 0;
    mc_list_item_t *curr = (mc_list_item_t *)list->head;
    do{
        if(i++==index) {
            *dst = curr->data;
            isFound = 1;
            break;
        }
    }while(NULL != (curr = curr->next));
    M_LIST_VALID(0 == isFound);
    return 0;
}

int mc_list_del(mc_list_t *list,void *data){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == data);

    mc_list_item_t *prev=NULL, *curr = NULL,*next = NULL;
    curr = (mc_list_item_t *)list->head;
    while(curr){
        next = curr->next;
        if(data == curr->data){
            if(NULL == prev){
                list->head = next;
            }else{
                prev->next = next;
            }
            _LIST_FREE_ITEM(list,curr);
            break;
        }
    }

    return 0;
}

int mc_list_for(mc_list_t *list,mc_list_for_f callback,void **data){
    int ret = 0;
    M_LIST_VALID(NULL == list);
    M_LIST_VALID(NULL == callback);

    int index = 0;
    mc_list_item_t *curr = (mc_list_item_t *)list->head;
    mc_list_item_t *next = NULL;
    while(curr){
        next = curr->next;
        R(callback(curr->data,index++,data));
        curr = next;
    }
    return 0;
}
