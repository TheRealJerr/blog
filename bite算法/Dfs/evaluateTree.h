/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 计算布尔二叉树的值
// 2025/2/7
bool func(bool l,bool r,int op)
{
    if(op == 2)
        return l | r;
    else 
        return l & r;
}
#include "../include/TreeNode.h"
class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        // 叶子节点
        if(root->left == nullptr && root->right == nullptr) return root->val == 1;

        // 支
        bool l = evaluateTree(root->left);
        bool r = evaluateTree(root->right);

        return func(l,r,root->val);
    }
};
