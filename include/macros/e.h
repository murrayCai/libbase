#ifndef __MACROS_E_H__
#define __MACROS_E_H__

#include "base.h"


#define E(expr) \
    do{\
        ret = (expr);\
        if(ret) { \
            exit(ret); \
        } \
    }while(0)

#define EL(expr,fmt,...) \
    do{ \
        ret = (expr);\
        if(ret) { \
            LOGE((fmt),##__VA_ARGS__);\
            LOGE("error code : [%d]\n",ret); \
            exit(ret); \
        } \
    }while(0)

#endif
