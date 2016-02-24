/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file socket.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/25 20:16:13
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "socket.h"
#include "packet_queue.h"
#include "packet.h"
#include "callback_map.h"
#include "packet_handler.h"
#include "comm_log.h"
#include <errno.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace lbs
{
    namespace net
    {
        pthread_mutex_t Socket::lock_ = PTHREAD_MUTEX_INITIALIZER;

        int Socket::init(const std::string host, const int port)
        {
            int ret = 0;

            memset((void*) (&host_address_), '\0', sizeof(host_address_));

            //判断是ip地址还是域名
            bool is_ip = true;

            for (unsigned int i = 0; i < host.size(); i++)
            {
                if (!('.' == host[i] || ('0' <= host[i] && host[i] <= '9')))
                {
                    is_ip = false;
                    break; 
                }
            }

            if (is_ip)
            {
                host_address_.sin_addr.s_addr = inet_addr(host.c_str());
            }

            else
            {
                //解析域名
                pthread_mutex_lock(&lock_);

                //返回内部静态变量，因此需要加锁
                struct hostent* host_str = gethostbyname(host.c_str());

                if (NULL != host_str)
                {
                    memcpy(&(host_address_.sin_addr), *(host_str->h_addr_list), sizeof(struct in_addr));
                }

                else
                {
                    COM_WRITELOG(COMLOG_WARNING, "sock init error [%s]", host.c_str());
                    ret = -1;
                }

                pthread_mutex_unlock(&lock_);
            }

            host_address_.sin_family = AF_INET;
            host_address_.sin_port = htons(port);

            return ret;
        }

        void Socket::set(const int fd, const struct sockaddr_in& host_address)
        {
            close(); 

            fd_ = fd;
            memcpy(&host_address_, &host_address, sizeof(host_address_));
        }

        int Socket::connect()
        {
            int ret = 0;

            if (-1 == (fd_ = socket(AF_INET, SOCK_STREAM, 0)))
            {
                ret = -1;
            }

            int reuse = 1;
            setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, (const void *) &reuse, sizeof(int));

            int alive = 1;
            setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, (const void *) &alive, sizeof(int));

            int sndbuf = 640000;
            setsockopt(fd_, SOL_SOCKET, SO_SNDBUF, (const void *) &sndbuf, sizeof(int));

            int rcvbuf = 640000;
            setsockopt(fd_, SOL_SOCKET, SO_RCVBUF, (const void *) &rcvbuf, sizeof(int));

            int no_delay = 1;
            setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, (const void *) &no_delay, sizeof(int));

            //write超时时间, 2s
            //int write_timeout = 2000;
            struct timeval write_timeout; 
            write_timeout.tv_sec = 2;
            write_timeout.tv_usec = 0;
            setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, 
                    (const void *) &write_timeout, sizeof(write_timeout));

            //read超时时间, 2s
            //int read_timeout = 2000;
            struct timeval read_timeout; 
            read_timeout.tv_sec = 2;
            read_timeout.tv_usec = 0;
            setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, 
                    (const void *) &read_timeout, sizeof(read_timeout));

            if (0 == ret)
            {
                ret = ::connect(fd_, (struct sockaddr*) &host_address_, sizeof(host_address_)); 
            }

            return ret;
        }

        /*
        int Socket::read(void* data, const int len)
        {
            int ret = 0;

            do
            {
                ret = ::read(fd_, data, len); 
            } while (ret < 0 && EINTR == errno); 

            return ret;
        }

        int Socket::write(const void* data, const int len)
        {
            int ret = 0; 

            do 
            {
                ret = ::write(fd_, data, len);
            } while (ret < 0 && EINTR == errno);

            return ret;
        }
        */

        int Socket::read()
        {
            int ret = 0;
            Packet* packet = new Packet(fd_);

            ret = packet->read();

            if (0 == ret)
            {
                if (callback_map_->has_callback(packet))
                {
                    ret = callback_map_->callback(packet); 
                }

                else
                {
                    packet_list_->add_packet(packet);
                }
            }

            return ret;
        }

        //only for test
        int Socket::write()
        {
            int ret = 0;
            char* data = "hello world";    
            
            if (0 >= ::write(fd_, data, strlen(data)))
            {
                ret = -1;
            }

            return ret;
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
