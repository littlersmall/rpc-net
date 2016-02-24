/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_socket.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 14:07:52
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <stdio.h>
#include "net_client.h"
#include "pb_packet.pb.h"

namespace lbs
{
    namespace net
    {
        class TestSocket
        {
            public:
            void test()
            {
                NetClient socket("127.0.0.1", 10001);

                socket.start();
                sleep(1);

                //case 1
                {
                    printf("\ncase 1:\n");
                    Pb* pb = new Pb;
                    Packet packet;

                    //packet.set_pb(pb);

                    pb->set_packet_code("lock");
                    pb->set_lock_name("hello/world");
                    pb->set_stat("lock");

                    Packet* recv_packet;

                    int ret = socket.syn_handle(packet, recv_packet);

                    if (0 == ret)
                    {
                        printf("stat is : %s\n", recv_packet->get_pb()->stat().c_str());
                    }

                    else
                    {
                        printf("ret = %d\n", ret);
                    }
                }


                //case 2
                {
                    printf("\ncase 2:\n");
                    Pb* pb = new Pb;
                    Packet packet;

                    packet.set_pb(pb);

                    pb->set_packet_code("lock");
                    pb->set_lock_name("hello/world");
                    pb->set_stat("lock");

                    Packet* recv_packet;

                    int ret = socket.syn_handle(packet, recv_packet);

                    if (0 == ret)
                    {
                        printf("stat is : %s\n", recv_packet->get_pb()->stat().c_str());
                    }

                    else
                    {
                        printf("ret = %d\n", ret);
                    }
                }

                //case 3
                {
                    printf("\ncase 3:\n");
                    Pb* pb = new Pb;
                    Packet packet;

                    packet.set_pb(pb);

                    pb->set_packet_code("lock");
                    pb->set_lock_name("hello/world");
                    pb->set_stat("lock");

                    Packet* recv_packet;

                    int ret = socket.syn_handle(packet, recv_packet);

                    if (0 == ret)
                    {
                        printf("stat is : %s\n", recv_packet->get_pb()->stat().c_str());
                    }

                    else
                    {
                        printf("ret = %d\n", ret);
                    }
                }

                //case 4
                {
                    printf("\ncase 4:\n");
                    Pb* pb = new Pb;
                    Packet packet;

                    packet.set_pb(pb);

                    pb->set_packet_code("lock");
                    pb->set_lock_name("hello/world");
                    pb->set_stat("unlock");

                    socket.write(packet);
                }

                //case 5
                {
                    printf("\ncase 5:\n");
                    Pb* pb = new Pb;
                    Packet packet;

                    packet.set_pb(pb);

                    pb->set_packet_code("echo");
                    pb->set_lock_name("hello/world");
                    pb->set_stat("test");

                    Packet* recv_packet;

                    while (1)
                    {
                        sleep(1);

                        int ret = socket.syn_handle(packet, recv_packet);
                        if (NULL != recv_packet)
                        {
                            delete recv_packet;
                        }

                        printf("ret = %d\n", ret);
                    }
                }

                socket.wait();
            }
        };
    }
}

int main()
{
    lbs::net::TestSocket test;

    test.test();
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
