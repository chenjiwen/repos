#ifndef __TREE_H__
#pragma once

#include "common.h"

typedef struct TreeNode TreeNode;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif // !__TREE_H__