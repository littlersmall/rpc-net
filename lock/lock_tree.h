/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lock_tree.h
 * @author xingyi01(xingyi01@baidu.com)
 * @date 2014/12/03 15:17:15
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __LOCK_TREE_H_
#define  __LOCK_TREE_H_

#include "lock_node.h"

namespace lbs
{
    namespace lock
    {
        class LockNode;

        class LockTree
        {
            LockNode* head_;
            bool real_file_;

            public:

            LockTree(std::string root_dir);

            bool lock(std::string lock_str, Memo memo);

            bool unlock(std::string lock_str);

            ~LockTree()
            {
                if (NULL != head_)
                {
                    delete head_;
                    head_ = NULL;
                } 
            }
        };
    }
}
















#endif  //__LOCK_TREE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
