/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file thread_pool.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/03/20 10:46:38
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __THREAD_POOL_H_
#define  __THREAD_POOL_H_

#include "thread.h"

namespace lbs
{
    namespace common
    {
        class ThreadPool : public Runnable
        {
            protected:
            int thread_count_;
            Thread* thread_array_;
            bool stop_;

            public:
            ThreadPool(int thread_count = 1);

            /**
             * @brief callback fun
             *
             * @param [in] thread   : Thread*
             * @return  void 
             * @todo 
            **/
            virtual void run(Thread* thread) = 0;

            /**
             * @brief 创建线程对象并启动每个线程
             *
             * @return  int 
             * @todo 
            **/
            int start();

            /**
             * @brief 停止所有线程(延时停止)
             *
             * @return  void 
             * @todo 
            **/
            void stop();

            /**
             * @brief 
             *
             * @return  void 
             * @todo 
            **/
            void wait();

            /**
             * @brief 
             *
             * @param [in] thread_count   : int
             * @return  void 
             * @todo 
            **/
            void set_thread_count(int thread_count);

            virtual ~ThreadPool();
        };
    }
}
















#endif  //__THREAD_POOL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
