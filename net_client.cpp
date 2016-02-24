/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file net_client.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/01 18:01:28
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "net_client.h"
#include "pb_packet.pb.h"
#include "comm_log.h"
#include <errno.h>
//#include "pb.h"

namespace lbs
{
    namespace net
    {
        void NetClient::run(common::Thread* /* thread*/)
        {
reconnect:
            while (0 != socket_.connect())
            {
                COM_WRITELOG(COMLOG_WARNING, "connect server failed");

                sleep(2);
            }

            socket_.regist();

            while (!stop_)
            {
                //重连
                if (reconnect_)
                {
                    printf("reconnect\n");
                    handle_error();
                    reconnect_ = false;
                    goto reconnect; 
                }

                std::vector<NetEvent*> events = epoll_.get_event(); 

                for (unsigned int i = 0; i < events.size(); i++)
                {
                    if (events[i]->get_ev() & (EPOLLERR | EPOLLHUP))
                    {
                        COM_WRITELOG(COMLOG_WARNING, "get_event error [%s]", strerror(errno));
                        handle_error();
                        goto reconnect;
                    }

                    if (events[i]->get_ev() & EPOLLIN)
                    {
                        if (0 != events[i]->read())
                        {
                            COM_WRITELOG(COMLOG_WARNING, "read error [%s]", strerror(errno));
                            handle_error();
                            goto reconnect;
                        }
                    }

                    //if (events[i]->get_ev() & EPOLLOUT)
                    //{
                    //}

                    events[i]->set_ev(0);
                }
                
                //int tmp = write(packet);
                //printf("tmp = %d\n", tmp);

                //usleep(1000*10);
            }
            
        }

        int NetClient::write(Packet& packet)
        {
            packet.set_fd(socket_.get_fd());

            int ret = packet.write();

            if (0 != ret)
            {
                if (-2 == ret || EPIPE == errno)
                {
                    //写超时 
                    //or
                    //socket关闭
                    //设置重连
                    reconnect_ = true;
                }
                //handle_error(&socket_);
                COM_WRITELOG(COMLOG_WARNING, "write to server errno[%d], error[%s]", 
                        errno, strerror(errno));
            }

            //printf("w ret = %d\n", ret);

            return ret;
        }

        int NetClient::syn_handle(Packet& send_packet, Packet*& recv_packet, int timeout)
        {
            int ret = 0;
            recv_packet = NULL;
            std::string uuid = send_packet.get_uuid();
            //1 ms
            static const int SLEEP_TIME = 1;
            int wait_time = 0;

            ret = write(send_packet);

            if (0 == ret)
            {
                while (true)
                {
                    Packet* packet = get_packet();

                    if (NULL != packet && packet->get_uuid() == uuid)
                    {
                        recv_packet = packet;
                        break;
                    }

                    else
                    {
                        delete packet;
                    }

                    wait_time += SLEEP_TIME;
                    usleep(SLEEP_TIME*1000);

                    if (wait_time >= timeout)
                    {
                        COM_WRITELOG(COMLOG_WARNING, "syn wait timeout packet_code[%s]", 
                                send_packet.get_packet_code().c_str());
                        ret = -2;
                        //设置重连
                        reconnect_ = true;

                        break;
                    }
                }
            }

            return ret;
        }

        void NetClient::handle_error()
        {
            COM_WRITELOG(COMLOG_WARNING, "close socket [%d]", socket_.get_fd());

            socket_.remove();
            socket_.close();
        }
    }
}


















/* vim: set ts=4 sw=4 sts=4 tw=100 */
