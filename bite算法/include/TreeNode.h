#pragma once
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val = 0,TreeNode* left = nullptr,TreeNode* right = nullptr):
        val(val),left(left),right(right)
    {}
};
