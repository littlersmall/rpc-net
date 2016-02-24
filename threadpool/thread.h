/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file thread.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/03/19 20:41:45
 * @version $Revision$ 
 * @brief 
 *  
 **/

#ifndef  __THREAD_H_
#define  __THREAD_H_
#include <pthread.h>
namespace lbs
{
    namespace common
    {
        class Thread;
        
        class Runnable
        {
            public:
            
            virtual void run(Thread* thread) = 0;
            virtual ~Runnable() {};
        };
        
        class Thread
        {
            pthread_t tid_;
            Runnable* runnable_;
            int thread_index_;
            /**
             * @brief
             *
             * @param [in] arg   : void*
             * @return  void* 
             * @todo 
            **/
            static void* callback(void* arg)
            {
                Thread* thread = (Thread*) arg;
                if (thread->get_runnable())
                {
                    thread->get_runnable()->run(thread); 
                }
                return (void*) NULL;
            }
            
            public:
             
            Thread()
            {
                tid_ = 0;
                runnable_ = NULL;
                thread_index_ = -1;
            }
            
            /**
             * @brief
             *
             * @param [in] index   : int
             * @return  void 
             * @todo 
            **/
            void set_thread_index(const int index)
            {
                thread_index_ = index;
            }
            
            /**
             * @brief 
             *
             * @return  int 
             * @todo 
            **/
            int get_thread_index()
            {
                return thread_index_;
            }
            
            /**
             * @brief callback
             *
             * @return  Runnable* 
             * @todo 
            **/
            Runnable* get_runnable()
            {
                return runnable_;
            }
            
            pthread_t get_tid()
            {
                return tid_;
            }
            
            /**
             * @brief 
             *
             * @param [in] runnable   : Runnable*
             * @return  int 
             * @todo 
            **/
            int start(Runnable* runnable)
            {
                runnable_ = runnable;
                return pthread_create(&tid_, NULL, Thread::callback, this);
            }
            
            void join()
            {
                if (tid_)
                {
                    pthread_join(tid_, NULL);
                    tid_ = 0;
                }
            }
        };
    }
}

#endif  //__THREAD_H_

















/* vim: set ts=4 sw=4 sts=4 tw=100 */
