/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_resource.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/05 14:31:28
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __LOCK_RESOURCE_H_
#define  __LOCK_RESOURCE_H_

#include "resource.h"
#include <map>
#include <string>

namespace lbs
{
    namespace net
    {
        //锁资源类
        //管理客户端持有的锁
        class LockResource : public Resource
        {
            std::map<std::string, int> lock_map_;

            public:

            bool add_resource(Packet* packet);
            bool rel_resource(Packet* packet);
            void del_resource(int fd);

            ~LockResource();
        };
    }
}
















#endif  //__LOCK_RESOURCE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
