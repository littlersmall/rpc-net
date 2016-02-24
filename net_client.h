/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file net_client.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 18:31:05
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __NET_CLIENT_H_
#define  __NET_CLIENT_H_

#include "epoll.h"
#include "socket.h"
#include "callback_map.h"
#include "packet_queue.h"
#include "thread_pool.h"
#include <sys/epoll.h>
#include <signal.h>

namespace lbs
{
    namespace net
    {
        //描述客户端接口
        class NetClient : public common::ThreadPool
        {
            Epoll epoll_;
            PacketQueue packet_list_;
            CallbackMap callback_map_;
            Socket socket_;
            volatile bool reconnect_;

            void handle_error();

            public:
            NetClient(const std::string host, const int port) : epoll_(), packet_list_(), 
                callback_map_(), socket_(&epoll_, &packet_list_, &callback_map_), reconnect_(false)
            {
                signal(SIGPIPE, SIG_IGN);

                if (0 != socket_.init(host, port))
                {
                    printf("client init error\n");
                }
            }

            void run(common::Thread* /* thread*/);

            /**
             * @brief 从消息队列中获得一个packet(调用方自己负责释放packet)
             *
             * @return  Packet* 
             * @todo 
            **/
            Packet* get_packet()
            {
                return packet_list_.get_packet();
            }

            /**
             * @brief 增加一个回调函数处理特定的类
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

            /**
             * @brief 向服务器发送数据
             *
             * @param [in/out] packet   : Packet&
             * @return  int 
             * @todo 
            **/
            int write(Packet& packet);

            /**
             * @brief 同步接口，timeout为超时时间(ms)
             *
             * @param [in/out] send_packet   : Packet&
             * @param [in/out] recv_packet   : Packet* &
             * @param [in/out] timeout   : int
             * @return  int 
             * @todo 
            **/
            int syn_handle(Packet& send_packet, Packet*& recv_packet, int timeout = 5000);
        };
    }
}
















#endif  //__NET_CLIENT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
