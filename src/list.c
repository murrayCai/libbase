#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define ERR_LIST_ITEM_NOT_FOUND 1
#define C_LIST_PARAM(expr) CHECK_PARAM((expr),MODULE_LIST)
#define C_LIST(expr,code) _CHECK(expr,(code),MODULE_LIST)

typedef struct list_item_s list_item_t;
struct list_item_s{
    void *data;
    list_item_t *next;
};

int list_free_defult(void *data){
    free(data);
    return 0;
}

int list_init(list_t **l,list_free_f f){
    CC(MALLOC_T(l,list_t));
    (*l)->free = f;
    return 0;
}

#define LIST_FREE_ITEM(list,item)\
    do{\
        if(NULL!=(list)->free){ \
            if(0 != (list)->free((item)->data))\
                LOGD("list free function has failed.\n");\
            CC(FREE_T(&(item),list_item_t));\
        }else{\
            LOGD("has no defined list free function.\n");\
        }\
    }while(0)

int list_free(list_t **list){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != *list);

    list_t *l = *list;
    list_item_t *curr = (list_item_t *)l->head,*next = NULL;
    while(curr){
        next = curr->next;
        LIST_FREE_ITEM(l,curr);
        curr = next;
    }

    FREE_T(list,list_t);
    return 0;
}

int list_add(list_t *list,void *data){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != data);

    list_item_t *item = NULL;
    CC(MALLOC_T(&item,list_item_t));
    item->data = data;

    if(NULL == list->tail){
        list->head = item;
        list->tail = item;
    }else{
        ((list_item_t*)list->tail)->next = item;
        list->tail = item;
    }

    list->size++;
    return 0;
}

int list_insert(list_t *list,void *data,unsigned int index){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != data);

    list_item_t *item = NULL;
    CC(MALLOC_T(&item,list_item_t));
    
    item->data = data;
    if(NULL == list->tail){
        list->head = item;
        list->tail = item;
    }else{

        if(index > list->size - 1){
            ((list_item_t *)list->tail)->next = item;
            list->tail = item;
        }else{
            int i = 0;
            list_item_t *prev = NULL;
            list_item_t *curr = (list_item_t *)list->head;
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

int list_index(void **dst,list_t *list,unsigned int index){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != dst);
    C_LIST_PARAM(index < list->size);

    int i = 0,isFound = 0;
    list_item_t *curr = (list_item_t *)list->head;
    do{
        if(i++==index) {
            *dst = curr->data;
            isFound = 1;
            break;
        }
    }while(NULL != (curr = curr->next));
    C_LIST(0 < isFound,ERR_LIST_ITEM_NOT_FOUND);
    return 0;
}

int list_del(list_t *list,void *data){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != data);

    list_item_t *prev=NULL, *curr = NULL,*next = NULL;
    curr = (list_item_t *)list->head;
    while(curr){
        next = curr->next;
        if(data == curr->data){
            if(NULL == prev){
                list->head = next;
            }else{
                prev->next = next;
            }
            LIST_FREE_ITEM(list,curr);
            break;
        }
    }

    return 0;
}

int list_for(list_t *list,list_for_f callback,void **data){
    C_LIST_PARAM(NULL != list);
    C_LIST_PARAM(NULL != callback);

    int index = 0;
    list_item_t *curr = (list_item_t *)list->head;
    list_item_t *next = NULL;
    while(curr){
        next = curr->next;
        CC(callback(curr->data,index++,data));
        curr = next;
    }
    return 0;
}

