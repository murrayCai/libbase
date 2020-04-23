#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"


typedef struct list_item_s list_item_t;
struct list_item_s{
    void *data;
    list_item_t *next;
};


list_t *list_init(list_free_f f){
    list_t *list = MALLOC_T(list_t);
    list->free = f;
    return list;
}

#define LIST_FREE_ITEM(list,item)\
    do{\
        if(NULL!=(list)->free){ \
            if(0 != (list)->free((item)->data))\
                LOGD("list free function has failed.\n");\
            FREE_T((item),list_item_t);\
        }else{\
            LOGD("has no defined list free function.\n");\
        }\
    }while(0)

int list_free(list_t *list){
    CHECK_PARAM(NULL!=list);
    list_item_t *curr = (list_item_t *)list->head,*next = NULL;
    while(curr){
        next = curr->next;
        LIST_FREE_ITEM(list,curr);
        curr = next;
    }

    FREE_T(list,list_t);
    return 0;
}

int list_add(list_t *list,void *data){
    CHECK_PARAM(NULL!=list);
    CHECK_PARAM(NULL!=data);

    list_item_t *item = MALLOC_T(list_item_t);
    RETURN_VAL_IF_FAIL(NULL!=item,ERR_MALLOC_NULL);
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
    CHECK_PARAM(NULL!=list);
    CHECK_PARAM(NULL!=data);

    list_item_t *item = MALLOC_T(list_item_t);
    RETURN_VAL_IF_FAIL(NULL!=item,ERR_MALLOC_NULL);
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

void *list_index(list_t *list,unsigned int index){
    RETURN_NULL_IF_CHECK_FAIL(NULL!=list);
    RETURN_NULL_IF_CHECK_FAIL(index < list->size);

    int i = 0;
    list_item_t *curr = (list_item_t *)list->head;
    do{
        if(i++==index) return curr->data;
    }while(NULL != (curr = curr->next));

    return NULL;
}

int list_del(list_t *list,void *data){
    CHECK_PARAM(NULL!=list);
    CHECK_PARAM(NULL!=data);

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
