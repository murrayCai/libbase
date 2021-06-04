#ifndef __MACROS_M_H__
#define __MACROS_M_H__

#include "base.h"

// return module the expr's code
#define M(expr,module) \
    do{\
        ret = (expr);\
        if(ret) __R(ERRNO(ret,(module)));\
    }while(0)

// return module expr's code and call func
#define MC(expr,func,module)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            __R(ERRNO(ret,(module)));\
        }\
    }while(0)

#define MG(expr,module,tag) \
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            goto tag;\
        }\
    }while(0)

// return module the expr's code and log it
#define ML(expr,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            __R( ERRNO(ret,(module)) );\
        }\
    }while(0)


#endif
