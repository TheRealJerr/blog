// create by hrj
// Current time: 2025-02-28 19:30:31.688
#include "/home/hrj/leetcode/headFile.h"
#include "../include/TreeNode.h"
// 锯齿形层序遍历
enum 
{
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT,
}; // 这里确定先放入left，还是right指针

// 这道题利用了两个栈帮助我们进行了解决
// s s_backup

// 类似于Linux进程队列中的dynamic和sleep的两个队列
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if(root == nullptr) return ret;
        // 锯齿形那就是利用栈
        // 创建两个栈交替使用
        std::stack<TreeNode*> s;
        std::stack<TreeNode*> s_backup;
        s.push(root);
        int status = LEFT_TO_RIGHT;
        while(!s.empty() || !s_backup.empty())
        {
            // 创建有效指针
            stack<TreeNode*>* valid_ptr = nullptr, *uvalid_ptr = nullptr;
            if(status == LEFT_TO_RIGHT)
            {
                valid_ptr = &s;
                uvalid_ptr = &s_backup;
            }
            else 
            {
                valid_ptr = &s_backup;
                uvalid_ptr = &s;
            }
            int sz = valid_ptr->size();
            vector<int> row; // 这一层的值
            for(int i = 0;i < sz;i++)
            {
                TreeNode* top = valid_ptr->top();
                valid_ptr->pop();
                row.push_back(top->val);
                if(status == LEFT_TO_RIGHT)
                {
                    if(top->left) uvalid_ptr->push(top->left);
                    if(top->right) uvalid_ptr->push(top->right);
                }
                else 
                {
                    if(top->right) uvalid_ptr->push(top->right);
                    if(top->left) uvalid_ptr->push(top->left);
                }
            }
            ret.push_back(std::move(row));
            // 切换方向
            status = (status == LEFT_TO_RIGHT ? RIGHT_TO_LEFT : LEFT_TO_RIGHT); 
        }
        return ret;
    }

};