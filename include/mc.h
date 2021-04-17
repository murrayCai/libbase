#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include "macros/macro.h"
#include "libmc_def.h"
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

int _log(log_lv_e lv,const char *file,int line,const char *fmt,...);
#define LOGD(fmt,...) \
    _log(LOG_LV_DEBUG,__FILE__,__LINE__,fmt,##__VA_ARGS__)
#define LOGI(fmt,...) \
    _log(LOG_LV_INFO,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGW(fmt,...) \
    _log(LOG_LV_WARN,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGE(fmt,...) \
    _log(LOG_LV_ERROR,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LEW(expr,fmt,...)\
    do{\
        if(!(expr)) LOGW(fmt,##__VA_ARGS__);\
    }while(0);

#define M_MI(index,module)\
    M((index) <= 0 || (index) >= MI_MAX,(module))


/* memory */
int malloc_t(void **p,size_t size,mi_e index,const char *name);
int malloc_tn(void **p,size_t count,size_t size,mi_e index,const char *name);
int free_t(void **pptr,size_t size,mi_e index);
int free_tn(void **pptr,size_t count,size_t size,mi_e index);

#define MALLOC_T(pptr,type) malloc_t((void **)(pptr),sizeof(type),MI_##type,#type)
#define MALLOC_TN(pptr,type,count) malloc_tn((void **)(pptr),(count),sizeof(type),MI_##type,#type)

#define FREE_T(pptr,type) free_t((void **)(pptr),sizeof(type),MI_##type)

#define FREE_TN(pptr,type,count) free_tn((void **)(pptr),(count),sizeof(type),MI_##type)

#define MALLOC_S(pptr,size) malloc_t((void **)(pptr),(size),MI_str,"str")
#define FREE_S(pptr,size)  free_t((void **)(pptr),(size),MI_str)

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
typedef int (*mc_list_for_f)(void *item,uint index,void **data);
int mc_list_for(mc_list_t *list,mc_list_for_f callback,void **data);
/* arr ptr */

typedef void * ptr_t;

typedef struct arr_s arr_t;
struct arr_s{
    uint count;
    uint used;
    ptr_t *data;
};
#define ARR_SIZE(arr)\
    ({\
     uint size = 0;\
     if(NULL != arr) size = arr->used;\
     (size);\
     })

int arr_init(arr_t **pp,uint count);
int arr_free(arr_t **arr);
int arr_add(arr_t *arr,void *data);
int arr_index(void **pp,arr_t *arr,uint index);

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
#endif
