/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file packet_queue.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 17:58:54
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __PACKET_QUEUE_H_
#define  __PACKET_QUEUE_H_

#include "packet.h"
#include <pthread.h>
#include <list>

namespace lbs
{
    namespace net
    {
        class PacketQueue
        {
            std::list<Packet*> packet_list_;
            pthread_mutex_t lock_;

            public:

            PacketQueue()
            {
                pthread_mutex_init(&lock_, NULL);
            }

            void add_packet(Packet* packet)
            {
                pthread_mutex_lock(&lock_);

                packet_list_.push_back(packet); 

                pthread_mutex_unlock(&lock_);
            }

            Packet* get_packet()
            {
                Packet* packet = NULL;

                pthread_mutex_lock(&lock_);
                
                if (!packet_list_.empty())
                {
                    packet = packet_list_.front();

                    packet_list_.pop_front();
                }

                pthread_mutex_unlock(&lock_);
                
                return packet;
            }
        };
    }
}
















#endif  //__PACKET_QUEUE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
