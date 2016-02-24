/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file net_event.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 16:06:20
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __NET_EVENT_H_
#define  __NET_EVENT_H_

#include "epoll.h"

namespace lbs
{
    namespace net
    {
        //描述一个事件
        //具体来说就是描述一个跟fd相关的事件
        //当socket读发生时触发
        class NetEvent
        {
            protected: 
            //public:
            int fd_;
            //描述事件类型,读or写or错误(目前只有读和错误事件，写是同步发生)
            int ev_;
            Epoll* epoll_;

            public:

            NetEvent(Epoll* e) : epoll_(e)
            {
                fd_ = -1;
                ev_ = 0;
            }

            virtual ~NetEvent() {};

            /**
             * @brief 处理异步读事件
             *
             * @return  int 
             * @todo 
            **/
            virtual int read() = 0;

            /**
             * @brief 处理异步写事件(目前不会触发)
             *
             * @return  int 
             * @todo 
            **/
            virtual int write() = 0;

            int get_fd()
            {
                return fd_;
            }

            /**
             * @brief 将本事件的fd注册到epoll中
             *
             * @return  int 
             * @todo 
            **/
            int regist()
            {
                return epoll_->add_event(this);
            }

            /**
             * @brief 删除epoll中和本fd相关的事件
             *
             * @return  int 
             * @todo 
            **/
            int remove()
            {
                return epoll_->remove_event(this);
            }

            void set_ev(int ev)
            {
                ev_ = ev;
            }

            int get_ev()
            {
                return ev_;
            }

            void close()
            {
                if (-1 != fd_)
                {
                    ::close(fd_);
                    fd_ = -1;
                }
            }
        };
    }
}
















#endif  //__NET_EVENT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
