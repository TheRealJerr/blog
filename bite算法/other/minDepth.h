//
// Created by jerry on 2024/9/4.
//
#include "headFile.h"
#ifndef LEETCODE_MINDEPTH_H
#define LEETCODE_MINDEPTH_H
struct TreeNode{
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int _val):val(_val)
    {}
};
int minDepth(TreeNode* root) {
    if(root == nullptr) return 0;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    if(left == 0 && right == 0) return 1;//叶子节点
    else if(left == 0 && right != 0) return right;
    else if(right == 0 && left != 0) return left;
    else return left < right ? (left + 1) : (right + 1);
}
void test()
{
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    n1->right = n2;
    n2->right = n3;
    n3->right = n4;
    n4->right = n5;
    int ret = minDepth(n1);
    cout << ret << endl;
}

#endif //LEETCODE_MINDEPTH_H
