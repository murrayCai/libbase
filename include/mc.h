#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include "macros/macro.h"
#include "libmc_def.h"

#ifndef MC_CALL_STACK_DEPTH
#define MC_CALL_STACK_DEPTH 64
#endif



/* module error */

typedef unsigned int error_code_t;
typedef struct {
    error_code_t *data;
    unsigned int index;
    size_t depth;
}call_stack_t;
int call_stack_push(unsigned int);
int call_stack_clear();
int call_stack_print();

/*
 * you should cp libbase_def.example libbase_def.h
 * and change libbase_def.h for your app
*/
// #define uint unsigned int

/* module log */
char *now_str();
typedef enum{
    LOG_LV_DEBUG,
    LOG_LV_INFO,
    LOG_LV_WARN,
    LOG_LV_ERROR
}log_lv_e;

#define LOG_LV_STR(lv)\
    ({\
     char *str = NULL;\
     if(LOG_LV_DEBUG == (lv)) str = "DEBUG";\
     else if(LOG_LV_INFO == (lv)) str = "INFO";\
     else if(LOG_LV_WARN == (lv)) str = "WARN";\
     else if(LOG_LV_ERROR == (lv)) str = "ERROR";\
     else str = "UNKOWN";\
     (str);\
     })

int _log(log_lv_e lv,int ret,const char *file,int line,const char *fmt,...);
#define LOGD(fmt,...) \
    _log(LOG_LV_DEBUG,ret,__FILE__,__LINE__,fmt,##__VA_ARGS__)
#define LOGI(fmt,...) \
    _log(LOG_LV_INFO,ret,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGW(fmt,...) \
    _log(LOG_LV_WARN,ret,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGE(fmt,...) \
    _log(LOG_LV_ERROR,ret,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LEW(expr,fmt,...)\
    do{\
        if(!(expr)) LOGW(fmt,##__VA_ARGS__);\
    }while(0);

#define MI_CHECK(index) ( (index) <= 0 || (index) >= MI_MAX )


/* memory */
typedef char str_t;
typedef struct {
    const char *name;
    uint used;
//    uint uCount;
    uint mCount;
    uint rCount;
    uint fCount;
    uint mTotal;
}mem_item_t;
int malloc_t(void **p,size_t size,mi_e index,const char *name);
int malloc_tn(void **p,size_t count,size_t size,mi_e index,const char *name);
int realloc_tn(void **p,size_t *count,size_t size,mi_e index,const char *name);
int free_t(void **pptr,size_t size,mi_e index);
int free_tn(void **pptr,size_t count,size_t size,mi_e index);

#define MALLOC_T(pptr,type) malloc_t((void **)(pptr),sizeof(type),MI_##type,#type)
#define MALLOC_TN(pptr,type,count) malloc_tn((void **)(pptr),(count),sizeof(type),MI_##type,#type)

#define REALLOC_TN(pptr,type,pCount) realloc_tn((void **)(pptr),(pCount),sizeof(type),MI_##type,#type)


#define FREE_T(pptr,type) free_t((void **)(pptr),sizeof(type),MI_##type)

#define FREE_TN(pptr,type,count) free_tn((void **)(pptr),(count),sizeof(type),MI_##type)

int mem_show();
int mem_finish();


/* list */
typedef int (*mc_list_free_f)(void *data);
typedef struct mc_list_s{
    uint size;
    void *head;
    void *tail;
    mc_list_free_f free;
}mc_list_t;
int mc_list_free_default(void *data);
int mc_list_init(mc_list_t **list,mc_list_free_f f);
int mc_list_free(mc_list_t **list);
int mc_list_add(mc_list_t *list,void *data);
int mc_list_insert(mc_list_t *list,void *data,unsigned int index);
int mc_list_index(void **dst,mc_list_t *list,unsigned int index);
int mc_list_del(mc_list_t *list,void *data);
int mc_list_del_without_callback(mc_list_t *list,void *data);
typedef int (*mc_list_for_f)(void *item,uint index,void **data);
int mc_list_for(mc_list_t *list,mc_list_for_f callback,void **data);
/* arr ptr */

typedef void * ptr_t;

typedef struct arr_s arr_t;
struct arr_s{
    size_t count;
    uint used;
    ptr_t *data;
};
#define ARR_SIZE(arr)\
    ({\
     uint size = 0;\
     if(NULL != arr) size = arr->used;\
     (size);\
     })
#define ARR_IS_FULL(arr) ( (arr)->used == (arr)->count )

int arr_init(arr_t **pp,uint count);
int arr_init_with_type_data(arr_t **pp,uint count,size_t size,mi_e index,const char *name);
int arr_free(arr_t **arr);
int arr_free_with_type_data(arr_t **pp,size_t size,mi_e index);
int arr_add(arr_t *arr,void *data);
int arr_shift(arr_t *arr,void *data);
int arr_add_with_type_data(void **dist,arr_t *arr,size_t size,mi_e index,const char *name);
int arr_index(void **pp,arr_t *arr,uint index);
int arr_delete_index(arr_t *arr,uint index);
int arr_delete_index_then_resort(arr_t *arr,uint index);
typedef int (*cb_arr_foreach)(uint index,void *data);
int arr_foreach(arr_t *arr,uint start,cb_arr_foreach f);
#define ARR_INIT_WITH_DATA(pp,count,type) \
    arr_init_with_type_data( (pp),(count),sizeof(type),MI_##type,#type)
#define ARR_FREE_WITH_DATA(pp,type) \
    arr_free_with_type_data( (pp),sizeof(type),MI_##type)
#define ARR_ADD_WITH_DATA(pp,p,type) \
    arr_add_with_type_data( (void **)(pp), (p),sizeof(type),MI_##type,#type)
#define ARR_FIRST(pp,p) arr_index( (void **)(pp),(p),0)
#define ARR_LAST(pp,p) arr_index((void **)(pp),(p), (0 >= (p)->used ) ? 0 : (p)->used - 1 )

/* key val */
typedef struct kv_s kv_t;
struct kv_s{
    char *key;
    char *val;
};

/* module date time */

#define DT_GET_NOW_YEAR() \
    ({\
     time_t t = time(NULL);\
     struct tm * dt = gmtime(&t);\
     (dt->tm_year + 1900);\
     })

#define DT_GET_NOW_MONTH() \
    ({\
     time_t t = time(NULL);\
     struct tm * dt = gmtime(&t);\
     (dt->tm_mon + 1);\
     })

#define GET_DAYS_OF_CURRENT_MONTH() get_days_of_month(DT_GET_NOW_YEAR(),DT_GET_NOW_MONTH()) 

int get_days_of_month(int year,int month);

// module mc
typedef struct{
    int isInit;
    call_stack_t callStack;
    mem_item_t *mItems;
    const char *modules[MC_MODULE_MAX];
}mc_t;
extern mc_t *mc;

int mc_init();
int mc_free();
int mc_call_stack_clear();

#define MC_INIT() if(NULL == mc || 0 == mc->isInit) EL(mc_init(),"libmc init failed!\n")

#endif
