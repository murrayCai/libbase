#ifndef __MACROS_L_H__
#define __MACROS_L_H__
#include "base.h"

// log if expr's true 
#define L(expr,fmt,...)\
    do{\
        ret = (expr);\
        if(ret) { \
            LOGW((fmt),##__VA_ARGS__);\
            LOGW("error code : [%d]\n",ret); \
        } \
    }while(0)

#define LC(expr,func,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW((fmt),##__VA_ARGS__); \
            LOGW("error code : [%d]\n",ret); \
            (func);\
        }\
    }while(0)


#endif
