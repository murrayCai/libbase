#ifndef __MACROS_BASE_H__
#define __MACROS_BASE_H__

#ifdef DEBUG
#define IS_DEBUG 1
#else
#define IS_DEBUG 0
#endif

#ifndef MODULE_CURR
#define MODULE_CURR 0
#endif

#define ERR_CODE_BASE 0
#define ERR_LINE_BASE 1000
#define ERR_MODULE_BASE (1000 * 10000)

#define ERRNO(code,module) \
    (ERR_CODE_BASE + errno + ERR_LINE_BASE * (__LINE__) + ERR_MODULE_BASE * MODULE_CURR)

#define MC_ERR_CLEAR() \
    do{\
        mc_call_stack_clear();\
        ret = 0;\
    }while(0)

#define __L_P() \
    do{ \
        call_stack_print();\
        mc_call_stack_clear();\
    }while(0)

#define __L_E(fmt,...) \
    do{\
        LOGE((fmt),##__VA_ARGS__);\
        __L_P();\
    }while(0)

#define __L_W(fmt,...) \
    do{\
        LOGW((fmt),##__VA_ARGS__);\
        __L_P();\
    }while(0)

#define __L_I(fmt,...) \
    do{\
        LOGI((fmt),##__VA_ARGS__);\
        __L_P();\
    }while(0)

#define __CHECK(expr) \
    ({\
     ret = (expr);\
     if(ret){ \
        call_stack_push(ERRNO(ret,MODULE_CURR));\
        if(NULL == mc->modules[MODULE_CURR]){\
            mc->modules[MODULE_CURR] = __FILE__;\
        }\
     }\
     (ret);\
     })

#define __R(code)\
    do{\
        if(IS_DEBUG){LOGI("%d",code);}\
        return code;\
    }while(0)

#endif
