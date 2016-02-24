/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file server.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 11:33:20
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __SERVER_H_
#define  __SERVER_H_

#include <pthread.h>
#include <string>
#include <vector>
#include "socket.h"
#include "net_event.h"
#include "callback_map.h"
#include "conn_sockets.h"

namespace lbs
{
    namespace net
    {
        class Socket;
        class PacketQueue;

        //描述一个server端口的事件
        class Server : public NetEvent
        {
            struct sockaddr_in my_address_;
            //描述每个socket持有的资源
            ConnSockets conn_sockets_;
            //接收到的所有未被处理的数据包
            PacketQueue* packet_list_;
            //回调函数集
            CallbackMap* callback_map_;

            Socket* accept();

            public:

            Server(Epoll* e, PacketQueue* pl, CallbackMap* cm) : NetEvent(e), packet_list_(pl),
                callback_map_(cm)
            {}

            ~Server();

            int init(const int port);
            int listen();

            /**
             * @brief accept一个socket
             *
             * @return  int 
             * @todo 
            **/
            int read();

            //没有写事件
            int write()
            {
                return 0; 
            };

            /**
             * @brief 获得当前和该server连接的所有socket的fd
             *
             * @return  std::vector<int> 
             * @todo 
            **/
            std::vector<int> get_fds()
            {
                return conn_sockets_.get_fds();
            }

            std::vector<NetEvent*> get_events()
            {
                return conn_sockets_.get_events();
            }

            /**
             * @brief 出错时删除和server连接的socket
             *
             * @param [in/out] event   : Event*
             * @return  void 
             * @todo 
            **/
            void remove_socket(NetEvent* event)
            {
                conn_sockets_.remove_socket(event);
            }
        };
    }
}
















#endif  //__SERVER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
