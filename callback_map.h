/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file callback_map.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/28 17:20:40
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __CALLBACK_MAP_H_
#define  __CALLBACK_MAP_H_

#include <map>
#include <vector>
#include <string>
#include <pthread.h>

namespace lbs
{
    namespace net
    {
        class Packet;
        class PacketHandler;

        //回调函数map
        //根据packet_code确定需要调用的回调函数
        class CallbackMap
        {
            std::map<std::string, std::vector<PacketHandler*> > fun_map_;
            pthread_mutex_t lock_;

            public:

            CallbackMap()
            {
                pthread_mutex_init(&lock_, NULL);
            }

            ~CallbackMap();

            /**
             * @brief 增加一个回调函数，new出来，由CallbackMap负责释放
             *
             * @param [in/out] packet_code   : std::string
             * @param [in/out] handler   : PacketHandler*
             * @return  void 
             * @todo 
            **/
            void regist_fun(std::string packet_code, PacketHandler* handler);

            std::vector<PacketHandler*> get_fun(std::string packet_code);

            /**
             * @brief 判断该packet是否被注册回调函数
             *
             * @param [in/out] packet   : Packet*
             * @return  bool 
             * @todo 
            **/
            bool has_callback(Packet* packet);

            /**
             * @brief 对一个packet调用回调函数
             *
             * @param [in/out] packet   : Packet*
             * @return  int 
             * @todo 
            **/
            int callback(Packet* packet);
        };
    }
}
















#endif  //__CALLBACK_MAP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
