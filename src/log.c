#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include "mc.h"

FILE * f = NULL;

int _log(log_lv_e lv,int ret,const char *file,int line,const char *fmt,...){
    if(NULL == f) f = stdout;

    printf("[%s]\t%s\t%s[%d]\t[ret :%d]\t(errno[%d]:%s)\t:",LOG_LV_STR(lv),now_str(),file,line,ret,errno,strerror(errno));

    va_list ap;
    va_start(ap,fmt);
    vfprintf(f,fmt,ap);
    va_end(ap);
    return 0;
}
