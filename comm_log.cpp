/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file comm_log.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/03/22 13:47:19
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "comm_log.h"

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/uio.h>
#include <sys/time.h>

namespace lbs
{
    namespace common
    {
        const char* ComLog::err_str_[] = {"FATAL", "WARNING", "NOTICE", "DEBUG"};

        ComLog::ComLog()
        {
            day_ = "NULL";
            real_time_ = true;
            fd_ = 2;
            real_fd_ = 2;

            //默认不开 debug
            level_ = COMLOG_NOTICE;

            log_file_path_name_="";
        }

        ComLog& ComLog::get_com_log()
		{
			static ComLog com_log;

			return com_log;
		}

        void ComLog::set_process_name(std::string name)
        {
        	process_name = name;
        }

        void ComLog::set_task_id(const int task_id, bool real_time)
        {

        }

        // real
        void ComLog::init()
        {
            set_task_id(-1, true);
        }

        void ComLog::init(const int task_id)
        {
            set_task_id(task_id, false); 
        }

        void ComLog::write_log(int level, const char* file, 
                int line, const char* function, pthread_t tid, const char* fmt, ...)
        {
            struct timeval tv;
            
            gettimeofday(&tv, NULL);
            struct tm tm; 
            ::localtime_r((const time_t*)&tv.tv_sec, &tm);

            char data1[4000] = {};
            char head[128] = {};

            va_list args;
            
            va_start(args, fmt);

            int data_size = vsnprintf(data1, 4000, fmt, args);

            va_end(args);

            if (data_size >= 4000)
            {   
              data_size = 3999;
            }   

            // remove trailing '\n'
            while (data1[data_size-1] == '\n') 
            {
                data_size --; 
            }

            data1[data_size] = '\0';

            int head_size = 
                snprintf(head,128,"[%04d-%02d-%02d %02d:%02d:%02d.%06ld] %-5s %s (%s:%d) [%ld] ",
                                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
                                tm.tm_hour, tm.tm_min, tm.tm_sec, tv.tv_usec,
                                err_str_[level], function, file, line, tid);

            struct iovec vec[3];

            vec[0].iov_base = head;
            vec[0].iov_len = head_size;
            vec[1].iov_base = data1;
            vec[1].iov_len = data_size;

            char NEWLINE[1] = {'\n'};

            vec[2].iov_base = NEWLINE;
            vec[2].iov_len = sizeof(NEWLINE);

            if (data_size > 0)
            {   
                if (real_time_)
                {
                    ::writev(real_fd_, vec, 3); 
                }

                else
                {
                    ::writev(fd_, vec, 3); 
                }
            }    
        }

        ComLog::~ComLog()
        {
            if (2 != fd_)
            {
                close(fd_);
            }

            if (2 != real_fd_)
            {
                close(real_fd_);
            }
        }

        void ComLog::set_log_level(const int level)
        {
            level_ = level;
        }

        std::string ComLog::get_log_file_path()
        {
        	return log_file_path_name_;
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
