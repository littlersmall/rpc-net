/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file resource.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/05 12:09:59
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __RESOURCE_H_
#define  __RESOURCE_H_

namespace lbs
{
    namespace net
    {   
        class Packet;

        //资源接口类
        class Resource
        {
            //std::string packet_code_;
            
            public:

            //获得资源
            virtual bool add_resource(Packet* packet) = 0;
            //释放资源
            virtual bool rel_resource(Packet* packet) = 0;
            //删除资源,(一般用于socket关闭时)
            virtual void del_resource(int fd) = 0;

            virtual ~Resource()
            {}
        };
    }
}
















#endif  //__RESOURCE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
