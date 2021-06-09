#ifndef __MI_H__
#define __MI_H__
#include "./defines/ex.h"
typedef enum{
    MODULE_MC,
    MODULE_MEM,
    MODULE_ERR,
    MODULE_LOG,
    MODULE_ARR,
    MODULE_LIST,
    MODULE_DT,
#ifdef MC_MODULE_DEFINE_EX
    MC_MODULE_DEFINE_EX,
#endif
    MC_MODULE_MAX
}module_e;

typedef enum{
    ERR_NONE,
    ERR_PARAM,
    ERR_PARAMS,
    ERR_MALLOC,
    ERR_MALLOC_NULL,
    ERR_LIST_FOR_F,
#ifdef MC_ERR_DEFINE_EX
    MC_ERR_DEFINE_EX,
#endif
    MC_ERR_MAX
}err_e;

typedef enum{
    MI_mem_item_t,
    MI_mc_t,
    MI_error_code_t,
    MI_ptr_t,
    MI_str_t,
    MI_arr_t,
    MI_kv_t,
    MI_mc_list_item_t,
    MI_mc_list_t,
#ifdef MC_MI_DEFINE_EX
    MC_MI_DEFINE_EX,
#endif
    MI_MAX
}mi_e;

#endif
