/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_node.cpp
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/03 15:39:58
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "lock_node.h"
#include "lock_tree.h"

namespace lbs
{
    namespace lock
    {
        LockTree::LockTree(std::string root_dir)
        {
            head_ = new LockNode();
            head_->set_name(root_dir);
        }

        bool LockTree::lock(std::string lock_str, Memo memo)
        {
            bool ret = true;

            if (head_->has_node(lock_str))
            {
                ret = false; 
            } 

            else
            {
                head_->add_node(lock_str, memo);
            }

            return ret;
        }

        bool LockTree::unlock(std::string lock_str)
        {
            bool ret = true;

            if (!head_->has_node(lock_str))
            {
                ret = false; 
            }

            else
            {
                head_->del_node(lock_str);
            }

            return ret;
        }
    }
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 */
