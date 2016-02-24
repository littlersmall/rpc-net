/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file resource_map.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/05 13:44:32
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __RESOURCE_MAP_H_
#define  __RESOURCE_MAP_H_

#include "net_event.h"
#include "resource.h"
#include <map>

namespace lbs
{
    namespace net
    {
        //资源管理中心
        //key为packet_code，value为resource
        class ResourceMap
        {
            std::map<std::string, Resource*> resource_map_;

            public:

            void regist_resource(std::string packet_code, Resource* resource)
            {
                resource_map_[packet_code] = resource; 
            } 

            void add_resource(Packet* packet)
            {
                resource_map_[packet->get_packet_code()]->add_resource(packet);
            }

            void rel_resource(Packet* packet)
            {
                resource_map_[packet->get_packet_code()]->rel_resource(packet);
            }

            void del_resource(NetEvent* event)
            {
                std::map<std::string, Resource*>::iterator iter = resource_map_.begin();

                for (; iter != resource_map_.end(); iter++)
                {
                    iter->second->del_resource(event->get_fd()); 
                }  
            }

            Resource* get_resource(std::string packet_code)
            {
                Resource* ret = NULL;

                if (resource_map_.end() != resource_map_.find(packet_code))
                {
                    ret = resource_map_[packet_code];
                }

                return ret;
            }

            ~ResourceMap()
            {
                std::map<std::string, Resource*>::iterator iter = resource_map_.begin();

                for (; iter != resource_map_.end(); iter++)
                {
                    delete iter->second; 
                }
            }
        }; 
    }
}
















#endif  //__RESOURCE_MAP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
