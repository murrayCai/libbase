#ifndef __MI_H__
#define __MI_H__

#define MC_MODULE_DEFINE 
#define MC_ERR_E
#define MC_MI_HEADERS

typedef enum{
    MODULE_MEM,
    MODULE_LOG,
    MODULE_ARR,
    MODULE_LIST,
    MC_MODULE_DEFINE
}module_e;

typedef enum{
    ERR_NONE,
    ERR_PARAM,
    ERR_PARAMS,
    ERR_MALLOC,
    ERR_MALLOC_NULL,
    ERR_LIST_FOR_F,
    MC_ERR_E
}err_e;
#define __MI_HEADERS_ \
    MI_mem,\
    MI_ptr_t,\
    MI_str,\
    MI_arr_t,\
    MI_kv_t,\
    MI_mc_list_item_t,\
    MI_mc_list_t

typedef enum{
    __MI_HEADERS_,
    MC_MI_HEADERS
    MI_MAX
}mi_e;

#endif
