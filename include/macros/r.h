#ifndef __MACRO_R_H_
#define __MACRO_R_H_
#include "./base.h"

// check expr/call + m
#define _R(expr,code,module) if(__CHECK(expr)) __R(ERRNO((code),(module)))

#define _RL(expr,code,module,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_W((fmt),##__VA_ARGS__);\
            __R(ERRNO((code),(module)));\
        }\
    }while(0)

// return return the expr's code
#define R(expr)  if(__CHECK(expr)) __R(ret)

#define RL_E(expr,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_E(fmt,##__VA_ARGS__);\
            __R(ret);\
        }\
    }while(0)

#define RL_W(expr,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_W(fmt,##__VA_ARGS__);\
            __R(ret);\
        }\
    }while(0)

#define RL_I(expr,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_I(fmt,##__VA_ARGS__);\
            __R(ret);\
        }\
    }while(0)
#define RL RL_W


// when call fun1 failed,then call fun2,return fun1's return code
#define RC(expr,call)\
    do{\
        if(__CHECK(expr)){\
            (call);\
            __R(ret);\
        }\
    }while(0)

#define RF(expr,func,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) func(##__VA_ARGS__);\
            __R(ret);\
        }\
    }while(0)

#endif
