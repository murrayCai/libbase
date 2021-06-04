#include "mc.h"

#ifdef MODULE_CURR
#undef MODULE_CURR
#define MODULE_CURR MODULE_MC
#endif

mc_t *mc = NULL;

static int mem_init(){
    int ret = 0;
    size_t size = sizeof(mem_item_t) * MI_MAX;
    mc->mItems = malloc(size);
    R(NULL == mc->mItems);
    memset(mc->mItems,0,size);
    mc->mItems[MI_mem_item_t].name = "mem_item_t";
    mc->mItems[MI_mem_item_t].used = size;
    mc->mItems[MI_mem_item_t].mCount = 1;
    mc->mItems[MI_mem_item_t].fCount = 0;
    mc->mItems[MI_mem_item_t].mTotal = size;
    return 0;
}

int mc_init(){
    int ret = 0;
    RL_E( (NULL != mc && 0 != mc->isInit),"libmc has inited!\n");
    size_t size = sizeof(mc_t);
    mc = (mc_t *)malloc(size);
    memset(mc,0,size);
    R(NULL == mc);
    RC(mem_init(),{ free(mc); mc = NULL; });
    
    mc->mItems[MI_mc_t].name = "mc_t";
    mc->mItems[MI_mc_t].used = size;
    mc->mItems[MI_mc_t].mCount = 1;
    mc->mItems[MI_mc_t].fCount = 0;
    mc->mItems[MI_mc_t].mTotal = size;

    mc->isInit = 1;
    RC(MALLOC_TN(&(mc->callStack.data),error_code_t,MC_CALL_STACK_DEPTH),
            { free(mc->mItems); mc->mItems = NULL; free(mc); mc = NULL;  }
        );
    mc->callStack.depth = MC_CALL_STACK_DEPTH;
    return ret;
}

int mc_free(){
    int ret = 0;
    RL_E( NULL == mc,"libmc has not init,could not free!\n");
    RL_E(FREE_TN(&(mc->callStack.data),error_code_t,mc->callStack.depth),"free libmc's error_code_t failed!\n");
    free(mc->mItems);
    RL_E(FREE_T(&mc,mc_t),"free libmc's mc_t failed!\n");
    return ret;
}
