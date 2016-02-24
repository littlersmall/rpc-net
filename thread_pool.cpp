/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file thread_pool.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/03/20 10:52:26
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "thread_pool.h"
#include <stdio.h>

namespace lbs
{
    namespace common
    {
        ThreadPool::ThreadPool(int thread_count)
        {
            stop_ = false;
            thread_count_ = thread_count;
            thread_array_ = NULL;
        }

        int ThreadPool::start()
        {
            int ret = 0;

            if (NULL != thread_array_ || 1 > thread_count_)
            {
                printf("start thread error, thread_array_ = %p, thread_count = %d",
                        thread_array_, thread_count_);

                ret = -1;
            } 

            else if (NULL != (thread_array_ = new Thread[thread_count_]))
            {
                for (int i = 0; i < thread_count_; i++)
                {
                    thread_array_[i].set_thread_index(i);

                    if (0 != (ret = thread_array_[i].start(this)))
                    {
                        break; 
                    }
                }
            }

            return ret;
        }

        void ThreadPool::stop()
        {
            stop_ = true;
        }

        void ThreadPool::wait()
        {
            if (NULL != thread_array_)
            {
                for (int i = 0; i < thread_count_; i++)
                {
                    thread_array_[i].join();
                }
            } 
        }

        void ThreadPool::set_thread_count(int thread_count)
        {
            if (NULL != thread_array_)
            {
                printf("runnning, cannot set thread_count\n");
            }

            else
            {
                thread_count_ = thread_count;
            }
        }

        ThreadPool::~ThreadPool()
        {
            if (NULL != thread_array_)
            {
                delete[] thread_array_;
                thread_array_ = NULL;
            } 
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
