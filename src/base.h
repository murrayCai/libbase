#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include "libbase_def.h"
/*
 * you should auto define mi_e
typedef enum{
    __MI_HEADERS_,
    MI_MAX
}mi_e;
*/
// #define uint unsigned int


#define FUNCTION(name,body,...) \
    int (name)(##__VA_ARGS__){ \
        int ret = 0; \
        (body); \
        return ret;\
    }

#define ERRNO(code,module) \
    ((code) + 1000 * (__LINE__) + 10000000 * (module))

// check expr/call + m
#define _R(expr,code,module)\
    do{\
        ret = (expr);\
        if(ret) return ERRNO((code),(module));\
    }while(0)

#define _RL(expr,code,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW((fmt),##__VA_ARGS__);\
            return ERRNO((code),(module));\
        }\
    }while(0)

// return return the expr's code
#define R(expr)\
    do{\
        ret = (expr);\
        if(ret) return ret;\
    }while(0);

// return module the expr's code
#define M(expr,module) \
    do{\
        ret = (expr);\
        if(ret) return ERRNO(ret,(module));\
    }while(0)

// when call func1 failed,then log warn about it
#define RL(expr,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            return ret;\
        }\
    }while(0);

// when call fun1 failed,then call fun2,return fun1's return code
#define RC(expr,func)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            return ret;\
        }\
    }while(0)

// when call func filed,then goto tag
#define G(expr,tag)\
    do{\
        ret = (expr);\
        if(ret){\
            goto tag;\
        }\
    }while(0)

// when call func failed, then call fun2 and goto tag
#define GC(expr,func,tag)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            goto tag;\
        }\
    }while(0)

// when call func failed, then goto error
#define GE(expr)\
    do{\
        ret = (expr);\
        if(ret){\
            goto error;\
        }\
    }while(0)

// if expr true then run func and log ,then goto tag
#define GCL(expr,func,tag,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            LOGW(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

// return module expr's code and call func
#define MC(expr,func,module)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            return ERRNO(ret,(module));\
        }\
    }while(0)

// return module the expr's code and log it
#define ML(expr,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            return ERRNO(ret,(module));\
        }\
    }while(0)

// log if expr's true 
#define L(expr,fmt,...)\
    do{\
        ret = (expr);\
        if(ret) LOGW((fmt),##__VA_ARGS__);\
    }while(0)

#define LC(expr,func,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW((fmt),##__VA_ARGS__);\
            (func);\
        }\
    }while(0)

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


/*
typedef enum{
    MI_mem,
    MI_ptr_t,
    MI_str,
    MI_arr_t,
    MI_kv_t,
    MI_list_item_t,
    MI_list_t,
    MI_request_t,
    MI_response_t,
    MI_http_t,
    MI_file_t,
    MI_Request,
    MI_Uri,
    MI_Uri__QueryEntry,
    MI_Request__FieldsEntry,
    MI_SSLInfo,
    MI_File,
    MI_Header,
    MI_Cookie,
    MI_app_t,
    MI_MAX
}mi_e;
*/

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
typedef int (*list_free_f)(void *data);
typedef struct list_s list_t;
struct list_s{
    uint size;
    void *head;
    void *tail;
    list_free_f free;
};
int list_free_defult(void *data);
int list_init(list_t **list,list_free_f f);
int list_free(list_t **list);
int list_add(list_t *list,void *data);
int list_insert(list_t *list,void *data,unsigned int index);
int list_index(void **dst,list_t *list,unsigned int index);
int list_del(list_t *list,void *data);
typedef int (*list_for_f)(void *item,uint index,void **data);
int list_for(list_t *list,list_for_f callback,void **data);
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
#endif
