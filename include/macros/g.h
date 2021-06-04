#ifndef __MACROS_G_H__
#define __MACROS_G_H__
#include "base.h"
// types : G / E /  M  /  C  / L
// when call func filed,then goto tag
#define G(expr,tag) if(__CHECK(expr)) goto tag

// when call func failed, then goto error
#define G_E(expr) if(__CHECK(expr)) goto error

// when call func failed, then call fun2 and goto tag
#define G_C(expr,tag,_call,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            goto tag;\
        }\
    }while(0)

#define GL_I(expr,tag,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_I(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define GL_W(expr,tag,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_W(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)


#define GL_E(expr,tag,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            __L_E(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define GL GL_W

// G_E
#define G_E_F(expr,func,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define G_F_E G_E_F

#define G_E_C(expr,_call)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            goto error;\
        }\
    }while(0)
#define G_C_E G_E_C

#define G_EL_E(expr,fmt,...) \
    do{\
        if(__CHECK(expr)){\
            __L_E(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_EL_W(expr,fmt,...) \
    do{\
        if(__CHECK(expr)){\
            __L_W(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_EL_I(expr,fmt,...) \
    do{\
        if(__CHECK(expr)){\
            __L_I(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define G_EL G_EL_W

// if expr true then run func and log ,then goto tag
#define G_CL_E(expr,tag,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_E(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_CL_W(expr,tag,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_W(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_CL_I(expr,tag,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_I(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_CL G_CL_W

// G F L
#define G_FL_E(expr,tag,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_E(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_FL_W(expr,tag,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_W(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_FL_I(expr,tag,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_I(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define G_FL G_FL_W

// G_E_CL
#define G_E_CL_E(expr,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_E(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_E_CL_W(expr,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_W(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_E_CL_I(expr,_call,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            (_call);\
            __L_I(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define G_E_CL G_E_CL_W

// G_E_FL
#define G_E_FL_E(expr,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_E(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_E_FL_W(expr,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_W(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)

#define G_E_FL_I(expr,func,fmt,...)\
    do{\
        if(__CHECK(expr)){\
            if(NULL != func) (func)(##__VA_ARGS__);\
            __L_I(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define G_E_FL G_E_FL_W
#endif
