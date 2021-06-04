#ifndef __MACRO_V_H_
#define __MACRO_V_H_
#include "./base.h"

// check expr/call + m
#define V(expr) if(expr) return;

#define VL(expr,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_W((fmt),##__VA_ARGS__);\
            return;\
        }\
    }while(0)

// when call fun1 failed,then call fun2,return fun1's return code
#define VC(expr,call)\
    do{\
        if(__CHECK(expr)){\
            (call);\
            return;\
        }\
    }while(0)

#define VF(expr,func,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) func(##__VA_ARGS__);\
            return;\
        }\
    }while(0)

#endif
