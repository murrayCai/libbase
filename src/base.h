#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
// #define uint unsigned int

typedef enum{
    ERR_NONE,
    ERR_PARAMS,
    ERR_MALLOC_NULL,
    ERR_LIST_FOR_F
}err_e;

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



#define RETURN_NULL_IF_FAIL(expr)\
    do{\
        if(!(expr)) return NULL;\
    }while(0)

#define RETURN_VAL_IF_FAIL(expr,val)\
    do{\
        if(!(expr)) return (val);\
    }while(0)

#define RETURN_IF_CHECK_FAIL(expr)\
    do{\
        if(!(expr)){\
            _log(LOG_LV_DEBUG,__FILE__,__LINE__,"check (%s) failed!\n",#expr);\
            return;\
        }\
    }while(0)

#define RETURN_NULL_IF_CHECK_FAIL(expr) \
    do{\
        if(!(expr)){\
            _log(LOG_LV_DEBUG,__FILE__,__LINE__,"check (%s) failed!\n",#expr);\
            return NULL;\
        }\
    }while(0)

#define RETURN_VAL_IF_CHECK_FAIL(expr,val) \
    do{\
        if(!(expr)){\
            _log(LOG_LV_DEBUG,__FILE__,__LINE__,"check (%s) failed!\n",#expr);\
            return (val);\
        }\
    }while(0)

#define CHECK_PARAM(expr) RETURN_VAL_IF_CHECK_FAIL((expr),ERR_PARAMS)
#define CHECK_PARAM_NULL(expr) RETURN_NULL_IF_CHECK_FAIL((expr))
#define CHECK_PARAM_VOID(expr) RETURN_IF_CHECK_FAIL((expr))


typedef enum{
    MI_mem,
    MI_ptr_t,
    MI_str,
    MI_arr_t,
    MI_kv_t,
    MI_list_item_t,
    MI_list_t,
    MI_uri_t,
    MI_MAX
}mi_e;


#define MALLOC(size) \
    ({\
     void *d = NULL;\
     d = malloc(size);\
     if(NULL==d){\
        LOGE("malloc %s failed!\n",size);\
     }\
     else{\
        memset(d,0,size);\
     } \
     (d);\
     })

/* memory */
#define MTN \
    uint mCount;\
    uint mSize;\
    mi_e mIndex;\
    const char *mName;

#define MTN_P uint count,uint size,mi_e index,const char *name 
void *malloc_t(size_t size,mi_e index,const char *name);
void *malloc_tn(size_t count,size_t size,mi_e index,const char *name);
void free_t(void *ptr,size_t size,mi_e index);
void free_tn(void *ptr,size_t count,size_t size,mi_e index);
#define MALLOC_T(type) (type *)malloc_t(sizeof(type),MI_##type,#type)
#define MALLOC_TN(type,count) (type *)malloc_tn((count),sizeof(type),MI_##type,#type)
#define FREE_T(ptr,type) free_t((ptr),sizeof(type),MI_##type)
#define FREE_TN(ptr,type,count) free_tn((ptr),(count),sizeof(type),MI_##type)

#define MALLOC_S(size) (char *)malloc_t(size,MI_str,"str")
#define FREE_S(ptr,size) free_t(ptr,size,MI_str)


int mem_init();
void mem_show();
void mem_finish();


/* list */
typedef int (*list_free_f)(void *data);
typedef struct list_s list_t;
struct list_s{
    uint size;
    void *head;
    void *tail;
    list_free_f free;
};
int list_free_defult(void *data);
list_t *list_init(list_free_f f);
int list_free(list_t *list);
int list_add(list_t *list,void *data);
int list_insert(list_t *list,void *data,unsigned int index);
void *list_index(list_t *list,unsigned int index);
int list_del(list_t *list,void *data);
typedef int (*list_for_f)(void *data,uint index);
int list_for(list_t *list,list_for_f callback);
/* arr ptr */

typedef void * ptr_t;

typedef struct arr_s arr_t;
struct arr_s{
    uint count;
    uint used;
    ptr_t *data;
};
arr_t *arr_init(uint count);
void arr_free(arr_t *arr);
int arr_add(arr_t *arr,void *data);
void *arr_index(arr_t *arr,uint index);

/* key val */
typedef struct kv_s kv_t;
struct kv_s{
    char *key;
    char *val;
};
#endif
