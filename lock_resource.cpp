/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_resource.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/05 15:08:41
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "lock_resource.h"
#include "lock_tree.h"
#include "lock_node.h"
#include "packet.h"
#include "pb_packet.pb.h"

namespace lbs
{
    namespace net
    {
        bool LockResource::add_resource(Packet* packet)
        {
            bool ret = false;
            std::string lock_name = packet->get_pb()->lock_name();
            lock::Memo memo;
            
            if (ret = GLOBAL_LOCK.lock(lock_name, memo))
            {
                lock_map_[lock_name] = packet->get_fd();
            }

            return ret;
        }

        bool LockResource::rel_resource(Packet* packet)
        {
            bool ret = false;
            std::string lock_name = packet->get_pb()->lock_name();

            if (ret = GLOBAL_LOCK.unlock(lock_name))
            {
                lock_map_.erase(lock_name);
            } 

            return ret;
        }

        void LockResource::del_resource(int fd)
        {
            printf("del fd = %d\n", fd);

            std::map<std::string, int>::iterator iter = lock_map_.begin();

            for (; iter != lock_map_.end(); iter++)
            {
                if (iter->second == fd)
                {
                    printf("lock is %s\n", iter->first.c_str());
                    GLOBAL_LOCK.unlock(iter->first);
                }
            }   
        }

        LockResource::~LockResource()
        {
            std::map<std::string, int>::iterator iter = lock_map_.begin();

            for (; iter != lock_map_.end(); iter++)
            {
                GLOBAL_LOCK.unlock(iter->first); 
            } 
        }
    }
}

















/* vim: set ts=4 sw=4 sts=4 tw=100 */
