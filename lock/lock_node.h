/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_node.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/03 14:55:03
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __LOCK_NODE_H_
#define  __LOCK_NODE_H_

#include <string>
#include <map>

namespace lbs
{
    namespace lock
    {
        typedef struct Memo
        {
            std::string owner;

            Memo(){}
            Memo(std::string o) : owner(o)
            {}
        }Memo;

        class LockNode
        {
            static const int REAL_FILE = 1;

            std::string name_;
            std::string full_name_;
            bool is_leaf_;
            Memo memo_;
            struct LockNode* father_;

            std::map<std::string, LockNode*> next_nodes_; 

            public:

            static std::string get_one_str(const std::string name_str, 
                    std::string& one, const char S = '/');

            LockNode(bool leaf = false) : is_leaf_(leaf), father_(NULL)
            {}

            void set_name(const std::string name, const std::string full_name = std::string())
            {
                name_ = name;

                if (full_name.empty())
                {
                    full_name_ = name;
                }

                else
                {
                    full_name_ = full_name + "/" + name;
                }
            }

            std::string get_name()
            {
                return name_;
            }

            void add_node(std::string name_str, Memo memo);

            bool has_node(std::string name_str);

            void del_node(std::string name_str);

            void real_file();
            void unlink();

            void print();

            ~LockNode();
        };
    }
}
















#endif  //__LOCK_NODE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
