#ifndef __MACRO_R_H_
#define __MACRO_R_H_
#include "./base.h"

// check expr/call + m
#define _R(expr,code,module)\
    do{\
        ret = (expr);\
        if(ret) return ERRNO((code),(module));\
    }while(0)

#define _RL(expr,code,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW((fmt),##__VA_ARGS__);\
            return ERRNO((code),(module));\
        }\
    }while(0)

// return return the expr's code
#define R(expr)\
    do{\
        ret = (expr);\
        if(ret) return ret;\
    }while(0);

// when call func1 failed,then log warn about it
#define RL(expr,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            return ret;\
        }\
    }while(0);

// when call fun1 failed,then call fun2,return fun1's return code
#define RC(expr,call)\
    do{\
        ret = (expr);\
        if(ret){\
            (call);\
            return ret;\
        }\
    }while(0)

#define RF(expr,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            if(NULL != func) func(##__VA_ARGS__);\
            return ret;\
        }\
    }while(0)

#endif
