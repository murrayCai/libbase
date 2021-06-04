#include <errno.h>
#include "mc.h"

#ifdef MODULE_CURR
#undef MODULE_CURR
#define MODULE_CURR MODULE_ERR
#endif

int call_stack_push(unsigned int errCodeNo){
    int ret = 0;
    MC_INIT();
    if(mc->callStack.index >= mc->callStack.depth){
       R(REALLOC_TN(&(mc->callStack.data),error_code_t,&(mc->callStack.depth)));
    }
    mc->callStack.data[mc->callStack.index++] = errCodeNo;
    return ret;
}

int mc_call_stack_clear(){
    int ret = 0;
    MC_INIT();
    memset(mc->callStack.data,0,sizeof(error_code_t) * mc->callStack.depth);
    mc->callStack.index = 0;
    return ret;
}

int call_stack_print(){
    int ret = 0;
    int i = 0;
    const char *file = NULL;
    unsigned int line = 0;
    unsigned int errCode = 0;
    unsigned int moduleIndex = 0;

    printf("[call stack]:\t[%d/%lu]\n",mc->callStack.index,mc->callStack.depth);
    for(;i < mc->callStack.index;i++){
        moduleIndex = ((mc->callStack.data[i])/ERR_MODULE_BASE);
        file = moduleIndex >= MC_MODULE_MAX ? "unknown module" : mc->modules[moduleIndex];
        line = ((mc->callStack.data[i]) % ERR_MODULE_BASE) / ERR_LINE_BASE;
        errCode = ((mc->callStack.data[i]) % ERR_LINE_BASE);
        printf("\t[%d]\t(%u/%u)%s:[%d]\tcode=%d\n",mc->callStack.data[i],moduleIndex,MC_MODULE_MAX,file,line,errCode);
    }
    printf("\t\n");
    return ret;
}
