#ifndef __MC_LIBNET_H__
#define __MC_LIBNET_H__


#define MC_MODULE_DEFINE_EX_NET \
    MODULE_NET_TCP_SERVER,\
    MODULE_NET_TCP_CLIENT,\
    MODULE_NET_PACK,\
    MODULE_NET_PACK_MANAGER

#define MC_MI_DEFINE_EX_NET \
    MI_tcp_server_t,\
    MI_tcp_server_config_t,\
    MI_tcp_server_client_t,\
    MI_ev_t,\
    MI_tcp_client_t,\
    MI_pack_t,\
    MI_pack_manager_t,\
    MI_pack_manager_item_t,\
    MI_pack_time_t,\
    MI_pack_no_t,\
    MI_pack_time_diff_t

#endif
