/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file packet_handler.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/28 17:27:03
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __PACKET_HANDLER_H_
#define  __PACKET_HANDLER_H_

#include "packet.h"
#include <time.h>

namespace lbs
{
    namespace net
    {
        class Packet;

        //包处理接口
        //接口类，用于描述CallbackMap中的回调类
        class PacketHandler
        {
            public:
            
            /**
             * @brief 用于处理一个packet
             *
             * @param [in/out] packet   : Packet*
             * @return  int 
             * @todo 
            **/
            virtual int handle_packet(Packet* packet) = 0;  
        };

        //将客户端的数据echo出来
        //用于测试
        class EchoHandler : public PacketHandler
        {
            public:

            int handle_packet(Packet* packet)
            {
                int recv_time = packet->get_recv_time();

                printf("test callback : %s\n", packet->get_packet_code().c_str()); 
                printf("recv_time is : %s\n", asctime(localtime((const time_t*) &recv_time))); 

                sleep(1);

                return packet->write();
            } 
        };
    }
}
















#endif  //__PACKET_HANDLER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
