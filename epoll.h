/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file epoll.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 14:51:47
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __EPOLL_H_
#define  __EPOLL_H_

#include <vector>

namespace lbs
{
    namespace net
    {
        class NetEvent;

        //描述epoll模型
        class Epoll
        {
            //epoll上注册的最大事件数
            const static int MAX_EVENTS = 1024;
            int fd_;
            
            public:

            Epoll();
            ~Epoll();

            /**
             * @brief 增加一个事件，目前有2种
             * 1. socket读事件
             * 2. server accept事件
             *
             * @param [in/out] event   : NetEvent*
             * @return  int 
             * @todo 
            **/
            int add_event(NetEvent* event);

            /**
             * @brief 删除一个事件，一般在出错时调用
             *
             * @param [in/out] event   : NetEvent*
             * @return  int 
             * @todo 
            **/
            int remove_event(NetEvent* event);

            /**
             * @brief 获得所有被触发的事件, 超时时间为timeout
             *
             * @param [in/out] timeout   : int
             * @return  std::vector<Event* > 
             * @todo 
            **/
            std::vector<NetEvent*> get_event(int timeout = 5000);
        };
    }
}
















#endif  //__EPOLL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
