/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file comm_log.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/03/22 13:19:02
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __COMM_LOG_H_
#define  __COMM_LOG_H_

/*
 * usage: COM_WRITELOG(COMLOG_NOTICE, "init error %s, ret[%d], "error", -1)
 */
#define COM_LOG_LEVEL(level) level, __FILE__, __LINE__, __FUNCTION__, pthread_self()
#define COM_LOGGER lbs::common::ComLog::get_com_log()
#define COM_PRINT(level, ...) COM_LOGGER.write_log(COM_LOG_LEVEL(level), __VA_ARGS__)
#define COM_LOG_BASE(level, ...) COM_PRINT(level, __VA_ARGS__)
#define COM_WRITELOG(level, _fmt_, args...) \
    ((COM_LOGGER.get_log_level() >= level) ? (COM_LOG_BASE(level, _fmt_, ##args)) : (void) 0)

#include <string>

namespace lbs
{
    static const int COMLOG_FATAL = 0;
    static const int COMLOG_WARNING = 1;
    static const int COMLOG_NOTICE = 2;
    static const int COMLOG_DEBUG = 3;

    namespace common
    {
        static const int COMLOG_FATAL = 0;
        static const int COMLOG_WARNING = 1;
        static const int COMLOG_NOTICE = 2;
        static const int COMLOG_DEBUG = 3;

        class ComLog
        {
            std::string day_;
            std::string log_path_;
            std::string log_file_path_name_;
            std::string process_name;
            bool real_time_;
            static const char* err_str_[];
            int fd_;
            int real_fd_;
            int level_;

            /**
             * @brief 
             *
             * @param [in] task_id   : const int
             * @param [in] real   : bool
             * @return  void 
             * @todo 
            **/
            void set_task_id(const int task_id, bool real_time);

            public:

            ComLog();

            /**
             * @brief 
             *
             * @param [in] level   : int
             * @param [in] file   : const char*
             * @param [in] line   : int
             * @param [in] function   : const char*
             * @param [in] tid   : pthread_t
             * @param [in] fmt   : const char*
             * @return  void 
             * @todo 
            **/
            void write_log(int level, const char* file, 
                    int line, const char* function, 
                    pthread_t tid, const char* fmt, ...);            

            /**
             * @brief 实时检查时初始化com_log
             *
             * @return  void 
             * @todo 
            **/
            void init();

            /**
             * @brief 非实时时初始化com_log
             *
             * @param [in] task_id   : int
             * @return  void 
             * @todo 
            **/
            void init(const int task_id);

            static ComLog& get_com_log();

            ~ComLog();

            void set_log_level(const int level);

            inline int get_log_level()
            {
                return level_;
            }

            void set_process_name(std::string name);

            std::string get_log_file_path();
        };
    }
}
















#endif  //__COMM_LOG_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
