/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file epoll.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 16:13:08
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "epoll.h"
#include "net_event.h"
#include <sys/epoll.h>

namespace lbs
{
    namespace net
    {
        Epoll::Epoll()
        {
            fd_ = epoll_create(MAX_EVENTS);
        }

        Epoll::~Epoll()
        {
            if (-1 != fd_)
            {
                ::close(fd_);
            }

            fd_ = -1;
        }

        int Epoll::add_event(NetEvent* event)
        {
            int ret = 0;
            struct epoll_event ev; 

            memset(&ev, 0, sizeof(ev));
            ev.events = 0;
            ev.data.ptr = event;

            //读
            ev.events |= EPOLLIN;
            //ev.events |= EPOLLOUT;
            ret = epoll_ctl(fd_, EPOLL_CTL_ADD, event->get_fd(), &ev); 

            return ret;
        }

        int Epoll::remove_event(NetEvent* event)
        {
            int ret = 0;
            struct epoll_event ev;

            memset(&ev, 0, sizeof(ev)); 
            ev.data.ptr = event; 
            ev.events = 0;

            ret = epoll_ctl(fd_, EPOLL_CTL_DEL, event->get_fd(), &ev);

            return ret; 
        }

        std::vector<NetEvent*> Epoll::get_event(int timeout)
        {
            std::vector<NetEvent*> ready_events;
            struct epoll_event events[MAX_EVENTS] = {};
 
            int num = epoll_wait(fd_, events, MAX_EVENTS, timeout);

            for (int i = 0; i < num; i++) 
            {
                if (events[i].events & (EPOLLERR | EPOLLHUP)) 
                {
                    printf("get_event error\n");
                }

                NetEvent* event = (NetEvent*) events[i].data.ptr;
                
                event->set_ev(events[i].events);
                ready_events.push_back(event);
            }
            
            return ready_events;
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
