/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file conn_sockets.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/01 20:31:04
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __CONN_SOCKETS_H_
#define  __CONN_SOCKETS_H_

#include "net_event.h"
#include <pthread.h>
#include <vector>

namespace lbs
{
    namespace net
    {
        //用于管理资源
        //1. 和server连接的socket
        class ConnSockets
        {
            pthread_mutex_t lock_;
            std::vector<NetEvent*> connect_sockets_;
             
            public:

            ConnSockets()
            {
                pthread_mutex_init(&lock_, NULL);
            }

            std::vector<NetEvent*> get_events()
            {
                pthread_mutex_lock(&lock_);
                std::vector<NetEvent*> events = connect_sockets_;
                pthread_mutex_unlock(&lock_);

                return events;
            }

            std::vector<int> get_fds()
            {
                std::vector<int> fds;

                pthread_mutex_lock(&lock_);

                for (unsigned int i = 0; i < connect_sockets_.size(); i++)
                {
                    fds.push_back(connect_sockets_[i]->get_fd());
                }

                pthread_mutex_unlock(&lock_);

                return fds;
            }

            void add_socket(NetEvent* event)
            {
                pthread_mutex_lock(&lock_);

                connect_sockets_.push_back(event);

                pthread_mutex_unlock(&lock_);
            }

            void remove_socket(NetEvent* event)
            {
                pthread_mutex_lock(&lock_);

                for (std::vector<NetEvent*>::iterator iter = connect_sockets_.begin(); 
                        iter != connect_sockets_.end();)
                {
                    if (event->get_fd() == (*iter)->get_fd())
                    {
                        delete (*iter);

                        iter = connect_sockets_.erase(iter); 
                    }

                    else
                    {
                        iter++;
                    }
                }

                pthread_mutex_unlock(&lock_);
            }

            ~ConnSockets()
            {
                for (unsigned int i = 0; i < connect_sockets_.size(); i++)
                {
                    delete connect_sockets_[i];
                }
            }
        };
    }
}
















#endif

/* vim: set ts=4 sw=4 sts=4 tw=100 */
