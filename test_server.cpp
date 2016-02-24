/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_server.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/11/26 14:03:04
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "net_server.h"
#include "lock_handler.h"
#include "lock_resource.h"

namespace lbs
{
    namespace net
    {
        class THandler : public PacketHandler
        {
            public:
            int handle_packet(Packet* packet)
            {
                printf("test callback : %s\n", packet->get_packet_code().c_str());

                return 0;
            } 
        };

        class TestServer
        {
            public:
            void test()
            {
                NetServer server(10001);

                server.regist_callback_fun("hello world", new THandler);
                server.regist_callback_fun("lock", new LockHandler(&server));
                server.regist_callback_fun("lock", new UnlockHandler(&server));
                server.regist_resource("lock", new LockResource);
                
                server.start();
                server.wait();

            }
        };

    }
}

int main()
{
    lbs::net::TestServer test;

    test.test();
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
