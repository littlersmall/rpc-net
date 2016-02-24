/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_handler.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/08 17:30:01
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __LOCK_HANDLER_H_
#define  __LOCK_HANDLER_H_

#include "packet_handler.h"
#include "net_server.h"
#include "packet.h"
#include "pb_packet.pb.h"
#include "comm_log.h"

namespace lbs
{
    namespace net
    {
        class LockHandler : public PacketHandler
        {
            NetServer* net_server_;

            public:

            LockHandler(NetServer* net_server) : net_server_(net_server)
            {}
            
            int handle_packet(Packet* packet)
            {
                int ret = 0;
                Resource* resource = net_server_->get_resource(packet->get_packet_code()); 

                if ("lock" == packet->get_pb()->stat() && NULL != resource)
                {
                    if (resource->add_resource(packet))
                    {
                        packet->get_pb()->set_stat("success");
                    }

                    else
                    {
                        packet->get_pb()->set_stat("fail");
                    }

                    ret = packet->write();
                }

                return ret;
            }
        };

        class UnlockHandler : public PacketHandler
        {
            NetServer* net_server_; 

            public:

            UnlockHandler(NetServer* net_server) : net_server_(net_server)
            {}

            int handle_packet(Packet* packet)
            {
                int ret = 0;
                Resource* resource = net_server_->get_resource(packet->get_packet_code());

                if ("unlock" == packet->get_pb()->stat() && NULL != resource)
                {
                    resource->rel_resource(packet);
                }

                return ret;
            }
        };
    }
}















#endif  //__LOCK_HANDLER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
