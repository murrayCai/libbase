#ifndef __MACROS_E_H__
#define __MACROS_E_H__

#include "base.h"


#define E(expr) if(__CHECK(expr)) exit(ret)

#define EL(expr,fmt,...) \
    do{ \
        if(__CHECK(expr)) { \
            LOGE("(errcode : %d)\t"fmt,ret,##__VA_ARGS__);\
            exit(ret); \
        } \
    }while(0)

#endif
