/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file net_server.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 18:12:33
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __NET_SERVER_H_
#define  __NET_SERVER_H_

#include "epoll.h"
#include "server.h"
#include "packet_queue.h"
#include "packet_handler.h"
#include "thread_pool.h"
#include "resource_map.h"
#include <errno.h>
#include <sys/epoll.h>
#include <signal.h>

namespace lbs
{
    namespace net
    {
        //server端对外接口类
        class NetServer : public common::ThreadPool
        {
            Epoll epoll_;
            PacketQueue packet_list_;
            CallbackMap callback_map_;
            ResourceMap resource_map_;
            Server server_;

            void handle_error(NetEvent* event);

            public:
            NetServer(const int port) : epoll_(), packet_list_(), callback_map_(),
                server_(&epoll_, &packet_list_, &callback_map_)
            {
                signal(SIGPIPE, SIG_IGN);

                if (0 != server_.init(port))
                {
                    printf("server init error\n");
                }

                //注册echo处理器
                //for test
                regist_callback_fun("echo", new EchoHandler);
            }

            void run(common::Thread* /* thread*/);

            /**
             * @brief 获得消息队列中的一个packet(获得方请负责释放packet)
             *
             * @return  Packet* 
             * @todo 
            **/
            Packet* get_packet()
            {
                return packet_list_.get_packet();
            }

            /**
             * @brief 增加一个回调函数处理特定的packet
             *
             * @param [in/out] packet_code   : std::string
             * @param [in/out] handler   : PacketHandler*
             * @return  void 
             * @todo 
            **/
            void regist_callback_fun(std::string packet_code, PacketHandler* handler)
            {
                callback_map_.regist_fun(packet_code, handler); 
            }

            void regist_resource(std::string packet_code, Resource* resource)
            {
                resource_map_.regist_resource(packet_code, resource); 
            }

            /**
             * @brief 广播数据
             *
             * @param [in/out] packet   : Packet&
             * @return  int 
             * @todo 
            **/
            int broadcast(Packet& packet);

            Resource* get_resource(std::string packet_code)
            {
                return resource_map_.get_resource(packet_code);
            }
        };
    }
}
















#endif  //__NET_SERVER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
