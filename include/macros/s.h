#ifndef __MACROS_S_H__
#define __MACROS_S_H__
#include "base.h"

#define S(expr) if(__CHECK(expr)) return

#define SC(expr,func,...)\
    do{\
        if(__CHECK(expr)){\
            _C(func,##__VA_ARGS__);\
            return ;\
        }\
    }while(0)

#define SF(expr,func,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) func(__VA_ARGS__);\
            return;\
        }\
    }while(0)


#endif
