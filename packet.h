/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file packet.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 17:51:46
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __PACKET_H_
#define  __PACKET_H_

#include <string>
#include <uuid/uuid.h>

namespace pb_net
{
    class PbPacket;
}

namespace lbs
{
    namespace net
    {
        //描述一个网络包
        typedef pb_net::PbPacket Pb;

        class Packet
        {
            //来自哪个fd
            //或需要发送到哪个fd
            int fd_;
            //protobuffer通信包
            //packet负责维护pb_的生存周期
            //因此set_pb()时请直接new
            Pb* pb_;

            std::string uuid_;

            //接收到包的时间
            int recv_time_;

            std::string generate_uuid()
            {
                char uuid_str[128] = {}; 

                uuid_t uuid;
                uuid_generate(uuid);

                uuid_unparse(uuid, uuid_str);

                return uuid_str;
            }

            //使用私有方法避免暴露接口
            void set_uuid(std::string uuid)
            {
                uuid_ = uuid;
            }

            public:

            Packet()
            {
                fd_ = -1;
                pb_ = NULL;

                uuid_ = generate_uuid();
                recv_time_ = 0;
            }

            std::string get_uuid()
            {
                return uuid_;
            }

            Packet(int fd) : fd_(fd)
            {
                pb_ = NULL; 
            }

            void set_fd(int fd)
            {
                fd_ = fd;
            }

            /**
             * @brief new一个pb指针传入
             *
             * @param [in/out] pb   : Pb*
             * @return  void 
             * @todo 
            **/
            void set_pb(Pb* pb);

            Pb* get_pb()
            {
                return pb_;
            }

            int get_fd()
            {
                return fd_;
            }

            std::string get_packet_code();

            /**
             * @brief 获取一个包的接收时间
             *
             * @return  int 
             * @todo 
            **/
            int get_recv_time()
            {
                return recv_time_;
            }

            /**
             * @brief 获取一个包的发送时间
             *
             * @return  int 
             * @todo 
            **/
            int get_send_time();

            /**
             * @brief 被epoll的读事件调用
             *
             * @return  int 
             * @todo 
            **/
            int read();

            /**
             * @brief 同步写数据(序列化pb包，并发送)
             *
             * @return  int 
             * @todo 
            **/
            int write(); 

            ~Packet();
        };
    }
}
















#endif  //__PACKET_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
