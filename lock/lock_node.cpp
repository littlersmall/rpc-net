/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_node.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/03 17:56:54
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "lock_node.h"
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

namespace lbs
{
    namespace lock
    {
        std::string LockNode::get_one_str(const std::string name_str, std::string& one, const char S)
        {
            std::string ret;
            std::string::size_type src_pos = 0;
            std::string::size_type dst_pos = 0;

            one = std::string();

            while (src_pos < name_str.size() && S == name_str[src_pos])
            {
                src_pos++; 
            }

            dst_pos = name_str.find_first_of(S, src_pos);

            if (std::string::npos != dst_pos)
            {
                one = name_str.substr(src_pos, dst_pos - src_pos);

                while (dst_pos < name_str.size() && S == name_str[dst_pos])
                {
                    dst_pos++;
                }

                ret =  name_str.substr(dst_pos, name_str.size() - dst_pos);
            }

            else if (src_pos < name_str.size())
            {
                one = name_str.substr(src_pos, name_str.size() - src_pos);
            }

            return ret;
        }

        void LockNode::add_node(std::string name_str, Memo memo)
        {
            if (name_str.empty())
            {
                return;
            }

            std::string name;
            std::string new_name_str = get_one_str(name_str, name); 

            if (next_nodes_.end() != next_nodes_.find(name))
            {
                next_nodes_[name]->add_node(new_name_str, memo);  
            }

            else
            {
                LockNode* new_node = new LockNode;

                new_node->father_ = this;
                next_nodes_[name] = new_node;
                //new_node->name_ = name;
                new_node->set_name(name, full_name_);

                if (new_name_str.empty())
                {
                    new_node->memo_ = memo; 
                    new_node->is_leaf_ = true;

                    new_node->real_file();
                }

                else
                {
                    new_node->real_file();
                    next_nodes_[name]->add_node(new_name_str, memo);        
                }
            }
        }

        bool LockNode::has_node(std::string name_str)
        {
            bool ret = false;

            if (name_str.empty())
            {
                ret = true;
            }

            else
            {
                std::string name;
                std::string new_name_str = get_one_str(name_str, name); 

                if (next_nodes_.end() != next_nodes_.find(name))
                {
                    if (new_name_str.empty())
                    {
                        ret = true;
                    }

                    else
                    {
                        ret = next_nodes_[name]->has_node(new_name_str);
                    }
                }

                else
                {
                    ret = false;
                }
            }

            return ret;
        }

        void LockNode::del_node(std::string name_str)
        {
            if (name_str.empty())
            {
                return;
            } 

            std::string name;
            std::string new_name_str = get_one_str(name_str, name);

            if (next_nodes_[name]->is_leaf_)
            {
                delete next_nodes_[name];

                next_nodes_.erase(name);
            }

            else
            {
                next_nodes_[name]->del_node(new_name_str);

                if (0 == next_nodes_[name]->next_nodes_.size())
                {
                    delete next_nodes_[name];

                    next_nodes_.erase(name);
                }
            }
        }

        void LockNode::real_file()
        {
            if (0 == REAL_FILE)
            {
                return; 
            }

            if (is_leaf_)
            {
                int fd = open(full_name_.c_str(), O_WRONLY | O_CREAT, 0644);
                //printf("errno: %s\n", strerror(errno));

                write(fd, memo_.owner.c_str(), memo_.owner.size()); 

                close(fd);
            }

            else
            {
                mkdir(full_name_.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
        }

        void LockNode::unlink()
        {
            if (REAL_FILE && name_ != full_name_)
            {
                printf("unlink : %s\n", full_name_.c_str());

                if (is_leaf_)
                {
                    ::unlink(full_name_.c_str()); 
                }

                else
                {
                    ::rmdir(full_name_.c_str());  
                }
            }
        }

        void LockNode::print()
        {
            //先序遍历 
            printf("lock name: %s, full_name : %s, is_leaf %d\n", name_.c_str(), full_name_.c_str(), is_leaf_);

            std::map<std::string, LockNode*>::iterator iter = next_nodes_.begin();

            for (iter; iter != next_nodes_.end(); iter++)
            {
                iter->second->print();
            }
        }

        LockNode::~LockNode()
        {
            std::map<std::string, struct LockNode*>::iterator iter = next_nodes_.begin();

            for (iter; iter != next_nodes_.end(); iter++)
            {
                if (NULL != iter->second)
                {
                    delete iter->second;
                    iter->second = NULL;
                }
            }

            unlink();
        }

    }
}

#include <iostream>
using namespace lbs::lock;
using namespace std;

int main()
{
    //case 1
    {
        cout << endl << "case 1" << endl;

        string lock_str = "a/b/c";
        
        while (!lock_str.empty())
        {
            string name;

            lock_str = LockNode::get_one_str(lock_str, name);

            cout << "name = " << name << endl;
            cout << "lock_str = " << lock_str << endl;
        }
    }

    //case 2
    {
        cout << endl << "case 2" << endl;

        string lock_str = "///a/b/c";
        
        while (!lock_str.empty())
        {
            string name;

            lock_str = LockNode::get_one_str(lock_str, name);

            cout << "name = " << name << endl;
            cout << "lock_str = " << lock_str << endl;
        }
    }

    //case 3
    {
        cout << endl << "case 3" << endl;

        string lock_str = "///a///b/c/";
        
        while (!lock_str.empty())
        {
            string name;

            lock_str = LockNode::get_one_str(lock_str, name);

            cout << "name = " << name << endl;
            cout << "lock_str = " << lock_str << endl;
        }
    }

    //case 4
    {
        cout << endl << "case 4" << endl;

        LockNode lock_node;

        lock_node.set_name(".");

        lock_node.add_node("a/b/c/", string("123"));
        lock_node.add_node("a/b/d/", string("123"));
        lock_node.add_node("a/b/e/", string("123"));
        lock_node.add_node("a/b/f/", string("123"));

        lock_node.print();
    }

    //case 5
    {
        cout << endl << "case 5" << endl;

        LockNode lock_node;

        lock_node.set_name(".");

        lock_node.add_node("a/b/c/", string("123"));
        lock_node.add_node("a/b/d/", string("123"));
        lock_node.add_node("a/b/e/", string("123"));
        lock_node.add_node("a/b/f/", string("123"));


        lock_node.del_node("/a/b/c");
        lock_node.del_node("/a/b/d");
        lock_node.del_node("/a/b/e");
        lock_node.del_node("/a/b/f");

        lock_node.print();
    }
}


















/* vim: set ts=4 sw=4 sts=4 tw=100 */
