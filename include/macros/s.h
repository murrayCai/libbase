#ifndef __MACROS_S_H__
#define __MACROS_S_H__
#include "base.h"

#define S(expr)\
    do{\
        ret = (expr);\
        if(ret) return;\
    }while(0);

#define SC(expr,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            _C(func,##__VA_ARGS__);\
            return ;\
        }\
    }while(0)

#define SF(expr,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            if(NULL != func) func(__VA_ARGS__);\
            return;\
        }\
    }while(0)


#endif
