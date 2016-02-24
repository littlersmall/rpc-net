/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file net_server.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/01 17:21:08
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "net_server.h"
#include "thread_pool.h"
#include "pb_packet.pb.h"
#include "comm_log.h"
#include <errno.h>

namespace lbs
{
    namespace net
    {
        void NetServer::run(common::Thread* /* thread*/)
        {
            int ret = 0;

            if (0 != (ret = server_.listen()))
            {
                printf("listen error : %d\n", ret);
            }

            else
            {
                server_.regist();

                while (!stop_)
                {
                    std::vector<NetEvent*> events = epoll_.get_event(); 

                    printf("events's size = %d\n", (int) events.size());

                    for (unsigned int i = 0; i < events.size(); i++)
                    {
                        //客户端主动断开连接触发 EPOLLIN
                        //int EPOLLRDHUP = 0x2000;
                        if (events[i]->get_ev() & (EPOLLERR | EPOLLHUP))
                        {
                            COM_WRITELOG(COMLOG_WARNING, "get_event error [%s]", strerror(errno));
                            handle_error(events[i]);

                            continue; 
                        }

                        if (events[i]->get_ev() & EPOLLIN)
                        {
                            //printf("fd = %d, ev = %d\n", events[i]->fd_, events[i]->ev_);
                            //printf("errno = %d, error is %s\n", errno, strerror(errno));
                            //printf("%x\n", events[i]);
                            //printf("fd = %d\n", events[i]->get_fd());
                            if (0 != events[i]->read())
                            {
                                COM_WRITELOG(COMLOG_WARNING, "read error [%s]", strerror(errno));
                                handle_error(events[i]);
                            }
                            //events[i]->write();
                        }

                        //if (events[i]->get_ev() & EPOLLOUT)
                        //{
                        //}

                        events[i]->set_ev(0);
                    }

                    //broadcast(packet);
                    //printf("errno = %d, error is %s\n", errno, strerror(errno));

                    //usleep(1000*10);
                }
            }
        }

        int NetServer::broadcast(Packet& packet)
        {
            int ret = 0;
            std::vector<NetEvent*> events = server_.get_events();

            for (unsigned int i = 0; i < events.size(); i++)
            {
                packet.set_fd(events[i]->get_fd());
                ret = packet.write();

                if (0 != ret)
                {
                    handle_error(events[i]);    
                }
            }

            return ret;
        }

        void NetServer::handle_error(NetEvent* event)
        {
            COM_WRITELOG(COMLOG_WARNING, "close socket [%d]", event->get_fd());

            server_.remove_socket(event);
            resource_map_.del_resource(event);
            event->remove();
            event->close();
        }
    }
}


















/* vim: set ts=4 sw=4 sts=4 tw=100 */
