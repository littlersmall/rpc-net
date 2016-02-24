/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file packet.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/28 14:41:27
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "packet.h"
#include "pb_packet.pb.h"
#include "comm_log.h"
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

namespace lbs
{
    namespace net
    {
        std::string Packet::get_packet_code()
        {
            return pb_->packet_code();
        }

        void Packet::set_pb(Pb* pb)
        {
            if (NULL != pb_)
            {
                delete pb_;
            }

            pb_ = pb;
            pb_->set_uuid(uuid_);
        }

        int Packet::get_send_time()
        {
            int time = 0;

            if (pb_)
            {
                time = pb_->send_time();
            }  

            return time;
        }


        //构造一个packet
        int Packet::read()
        {
            pb_ = new Pb();

            int ret = 0;
            int size = 0;
            int res = ::read(fd_, &size, sizeof(size));

            if (res > 0)
            {
                size = ntohl(size);
                //char data_buf[1024] = {};
                std::string data_buf;

                data_buf.resize(size);

                //res = ::read(fd_, data_buf, size);
                res = ::read(fd_, (char*) data_buf.data(), size);

                if (res > 0)
                {
                    if (!pb_->ParseFromString(data_buf))
                    {
                        COM_WRITELOG(COMLOG_WARNING, "pb parse error");
                        ret = -1;
                    } 
                    
                    else
                    {
                        set_uuid(pb_->uuid());
                        recv_time_ = time(NULL);
                    }
                }

                else
                {
                    COM_WRITELOG(COMLOG_WARNING, "read error [%s]", strerror(errno));
                    ret = -1;

                    if (EAGAIN == errno)
                    {
                        //超时
                        ret = -2;
                    }
                }
            }

            else
            {
                COM_WRITELOG(COMLOG_WARNING, "read error [%s]", strerror(errno));
                ret = -1;

                if (EAGAIN == errno)
                {
                    //超时
                    ret = -2;
                }
            }

            printf("buf is %s, ret = %d\n", pb_->packet_code().c_str(), ret);

            return ret;
        }

        int Packet::write()
        {
            int ret = 0;
            std::string data_buf;
            
            if (NULL == pb_)
            {
                ret = -1;
                COM_WRITELOG(COMLOG_WARNING, "pb is NULL");
            }

            else
            {
                pb_->set_send_time(time(NULL)); 
                
                if (!pb_->SerializeToString(&data_buf))
                {
                    COM_WRITELOG(COMLOG_WARNING, "pb serialize error");
                    ret = -1;
                }
            }

            if (0 == ret)
            {
                //写一次
                uint32_t size = htonl(data_buf.size());
                std::string send_data;

                send_data.resize(sizeof(size) + data_buf.size());

                memcpy((char*) &send_data[0], &size, sizeof(size));
                memcpy(((char*) &send_data[0] + sizeof(size)), data_buf.c_str(), data_buf.size());

                int res = ::write(fd_, send_data.c_str(), send_data.size());

                if (res <= 0)
                {
                    COM_WRITELOG(COMLOG_WARNING, "write error [%s]", strerror(errno));
                    ret = -1; 

                    if (EAGAIN == errno)
                    {
                        //超时
                        ret = -2;
                    }
                }

                //写2次
                //1 写大小
                //2 写数据
                /*
                int size = data_buf.size();
                int res = ::write(fd_, &size, sizeof(size));

                if (res > 0)
                {
                    res = ::write(fd_, data_buf.c_str(), size);

                    if (res <= 0)
                    {
                        COM_WRITELOG(COMLOG_WARNING, "write error [%s]", strerror(errno));
                        ret = -1; 

                        if (EAGAIN == errno)
                        {
                            //超时
                            ret = -2;
                        }
                    }
                }

                else
                {
                    COM_WRITELOG(COMLOG_WARNING, "write error [%s]", strerror(errno));
                    ret = -1;

                    if (EAGAIN == errno)
                    {
                        //超时
                        ret = -2;
                    }
                }
                */
            }

            return ret;
        }

        Packet::~Packet()
        {
            if (NULL != pb_)
            {
                delete pb_;
                pb_ = NULL;
            }
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
