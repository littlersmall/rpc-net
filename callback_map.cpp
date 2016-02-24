/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file callback_map.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/01 17:08:21
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "callback_map.h"
#include "packet.h"
#include "packet_handler.h"

namespace lbs
{
    namespace net
    {
        void CallbackMap::regist_fun(std::string packet_code, PacketHandler* handler)
        {
            pthread_mutex_lock(&lock_);

            if (fun_map_.end() == fun_map_.find(packet_code))
            {
                std::vector<PacketHandler*> fun_vec;

                fun_vec.push_back(handler);   
                fun_map_[packet_code] = fun_vec;
            } 

            else
            {
                fun_map_[packet_code].push_back(handler);
            }

            pthread_mutex_unlock(&lock_);
        }

        std::vector<PacketHandler*> CallbackMap::get_fun(std::string packet_code)
        {
            std::vector<PacketHandler*> fun_vec;

            pthread_mutex_lock(&lock_);

            if (fun_map_.end() != fun_map_.find(packet_code))
            {
                fun_vec = fun_map_[packet_code];
            } 

            pthread_mutex_unlock(&lock_);

            return fun_vec;
        }

        bool CallbackMap::has_callback(Packet* packet)
        {
            int ret = false;

            pthread_mutex_lock(&lock_);

            if (fun_map_.end() != fun_map_.find(packet->get_packet_code()))
            {
                ret = true; 
            }

            pthread_mutex_unlock(&lock_);

            return ret;
        }

        int CallbackMap::callback(Packet* packet)
        {
            int ret = 0;
            std::vector<PacketHandler*> fun_vec = get_fun(packet->get_packet_code()); 

            for (unsigned int i = 0; i < fun_vec.size(); i++)
            {
                if (0 == ret)
                {
                    ret = fun_vec[i]->handle_packet(packet);
                }

                else
                {
                    break;
                }
            }

            if (NULL != packet)
            {
                delete packet;
            }

            return ret;
        }

        CallbackMap::~CallbackMap()
        {
            std::map<std::string, std::vector<PacketHandler*> >::iterator iter = fun_map_.begin();

            for (; iter != fun_map_.end(); iter++)
            {
                for (unsigned int i = 0; i < iter->second.size(); i++)
                {
                    delete iter->second[i];
                }
            }
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
