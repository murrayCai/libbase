#ifndef __MC_EX_DEFINES_H__
#define __MC_EX_DEFINES_H__

#include "./libmd.h"
#include "./generator.h"
#include "./libnet.h"
#include "./ws_server.h"

#define MC_MODULE_DEFINE_EX \
    MC_MODULE_DEFINE_EX_MD,\
    MC_MODULE_DEFINE_EX_GENERATOR,\
    MC_MODULE_DEFINE_EX_NET,\
    MC_MODULE_DEFINE_EX_WS_SERVER

// #define MC_ERR_DEFINE_EX 


#define MC_MI_DEFINE_EX \
    MC_MI_DEFINE_EX_MD,\
    MC_MI_DEFINE_EX_GENERATOR,\
    MC_MI_DEFINE_EX_NET,\
    MC_MI_DEFINE_EX_WS_SERVER


#endif
