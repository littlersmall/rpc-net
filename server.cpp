/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file server.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 11:43:37
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "server.h"
#include <sys/poll.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/tcp.h>

namespace lbs
{
    namespace net
    {
        int Server::init(const int port)
        {
            int ret = 0;

            memset((void*) (&my_address_), '\0', sizeof(my_address_));

            my_address_.sin_family = AF_INET;
            my_address_.sin_port = htons(port);
            my_address_.sin_addr.s_addr = htonl(INADDR_ANY);

            if (-1 == (fd_ = socket(AF_INET, SOCK_STREAM, 0)))
            {
                ret = -1;
            }

            return ret;
        }

        int Server::listen()
        {
            int ret = 0;
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

            if (::bind(fd_, (struct sockaddr *) &my_address_, sizeof(my_address_)) < 0) 
            {
                ret = -1;
            }   

            else if (::listen(fd_, 256) < 0) 
            {                                                         
                ret = -1;
            }

            return ret;
        }

        Socket* Server::accept()
        {
            Socket* new_socket = new Socket(epoll_, packet_list_, callback_map_);
            struct sockaddr_in addr;
            int len = sizeof(addr);
            int fd = ::accept(fd_, (struct sockaddr*) &addr, (socklen_t*) &len);

            if (fd > 0)
            {
                int reuse = 1;
                setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &reuse, sizeof(int));

                int alive = 1;
                setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const void *) &alive, sizeof(int));

                int sndbuf = 640000;
                setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (const void *) &sndbuf, sizeof(int));

                int rcvbuf = 640000;
                setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (const void *) &rcvbuf, sizeof(int));

                int no_delay = 1;
                setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const void *) &no_delay, sizeof(int));

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

                new_socket->set(fd, addr); 
            }        

            else
            {
                printf("fd erri%d\n", fd);
            }


            return new_socket;
        }

        int Server::read()
        {
            int ret = 0;

            Socket* socket = accept();

            //socket->connect();
            //if (0 == (ret = socket.connect()))
            //{
            //if (times == 1)
            //{

            conn_sockets_.add_socket(socket);
            socket->regist();

            //printf("connect_cockets_.back() = %d, %x\n", connect_sockets_.back().get_fd(), &(connect_sockets_.back()));
            //}
            //}

            return ret;
        }

        Server::~Server()
        {
            close();
        }
    }
}


















/* vim: set ts=4 sw=4 sts=4 tw=100 */
