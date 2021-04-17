#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mc.h"

FILE * f = NULL;

int _log(log_lv_e lv,const char *file,int line,const char *fmt,...){
    if(NULL == f) f = stdout;

    printf("[%s]  %s  %s(%d):",LOG_LV_STR(lv),now_str(),file,line);

    va_list ap;
    va_start(ap,fmt);
    vfprintf(f,fmt,ap);
    va_end(ap);
    return 0;
}
