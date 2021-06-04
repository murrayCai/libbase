#ifndef __MACROS_L_H__
#define __MACROS_L_H__
#include "base.h"
#include <errno.h>

// log if expr's true 
#define L_W(expr,fmt,...) \
    if(__CHECK(expr)) __L_W((fmt),##__VA_ARGS__)

#define L_I(expr,fmt,...) \
    if(__CHECK(expr)) __L_I((fmt),##__VA_ARGS__)

#define L_E(expr,fmt,...)\
    if(__CHECK(expr)) __L_E((fmt),##__VA_ARGS__)

#define L L_W

#define LC(expr,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_W((fmt),##__VA_ARGS__); \
            (func);\
        }\
    }while(0)


#endif
