/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file socket.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/25 20:06:53
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __SOCKET_H_
#define  __SOCKET_H_

#include "net_event.h"
#include <string>
#include <pthread.h>
#include <netinet/in.h>

namespace lbs
{
    namespace net
    {
        class PacketQueue;
        class CallbackMap;

        //描述一个socket
        class Socket : public NetEvent
        {
            struct sockaddr_in host_address_;
            //锁静态变量
            static pthread_mutex_t lock_;
            PacketQueue* packet_list_;
            CallbackMap* callback_map_;

            public:

            Socket(Epoll* e, PacketQueue* pl, CallbackMap* cm) : NetEvent(e), packet_list_(pl),
                callback_map_(cm)
            {}

            int init(const std::string host, const int port);

            void set(const int fd, const struct sockaddr_in& host_address);

            int connect();

            //int read(void* data, const int len);
            //int write(const void* data, const int len);

            /**
             * @brief 读取来自该socket的数据
             *
             * @return  int 
             * @todo 
            **/
            int read();
            int write();
        };
    }
}
















#endif  //__SOCKET_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
