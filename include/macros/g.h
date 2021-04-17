#ifndef __MACROS_G_H__
#define __MACROS_G_H__
#include "base.h"
// types : G / E /  M  /  C  / L
// when call func filed,then goto tag
#define G(expr,tag) \
    do{ret = (expr); if(ret) goto tag; }while(0)


// when call func failed, then goto error
#define GE(expr) \
    do{ ret = (expr); if(ret) goto error; }while(0)

// when call func failed, then call fun2 and goto tag
#define GC(expr,tag,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            goto tag;\
        }\
    }while(0)

#define GL(expr,tag,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)

#define GM(expr,tag,module) \
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            goto tag;\
        }\
    }while(0)

// GE
#define GEF(expr,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            if(NULL != func) (func)(__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define GFE GEF

#define GEC(expr,call)\
    do{\
        ret = (expr);\
        if(ret){\
            (call);\
            goto error;\
        }\
    }while(0)
#define GCE GEC

#define GEL(expr,fmt,...) \
    do{\
        ret = (expr);\
        if(ret){\
            LOGW(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define GLE GEL

#define GEM(expr,module) \
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            goto error;\
        }\
    }while(0)
#define GME GEM



// if expr true then run func and log ,then goto tag
#define GCL(expr,tag,func,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            LOGW(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)
#define GLC  GCL

#define GMC(expr,tag,module,func,...)\
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            (func);\
            goto tag;\
        }\
    }while(0)
#define GCM  GMC

#define GLM(expr,tag,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            LOGW(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)
#define GML  GLM

#define GECM(expr,func,module)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            ret = ERRNO(ret,(module));\
            goto error;\
        }\
    }while(0)
#define GEMC GECM
#define GMEC GECM
#define GMCE GECM
#define GCEM GECM
#define GCME GECM

#define GECL(expr,func,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            (func);\
            LOGW(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define GELC GECL
#define GLEC GECL
#define GLCE GECL
#define GCEL GECL
#define GCLE GECL

#define GEML(expr,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            LOGW(fmt,##__VA_ARGS__);\
            goto error;\
        }\
    }while(0)
#define GELM GEML
#define GLEM GEML
#define GLME GEML
#define GMEL GEML
#define GMLE GEML

#define GCML(expr,tag,func,module,fmt,...)\
    do{\
        ret = (expr);\
        if(ret){\
            ret = ERRNO(ret,(module));\
            LOGW(fmt,##__VA_ARGS__);\
            goto tag;\
        }\
    }while(0)
#define GCLM GCML
#define GLCM GCML
#define GLMC GCML
#define GMCL GCML
#define GMLC GCML

#endif
