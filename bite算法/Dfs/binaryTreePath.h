#include "../headFile.h"
#include "../include/TreeNode.h"

#define __VERSION_2.0__

const std::string link_flag = "->";

#ifdef __VERSION_1.0__
class Solution {
    public:
        vector<string> binaryTreePaths(TreeNode* root) {
            // 虽然右值支持拷贝返回高效性
            std::vector<std::string> ret;
            Dfs(root,ret);
            return ret;
        }
        std::pair<int,int> Dfs(TreeNode* root,std::vector<std::string>& ret) // 返回值是区间
        {
            if(root == nullptr) return std::make_pair(-1,-1);
            auto l_area = Dfs(root->left,ret);
            auto r_area = Dfs(root->right,ret);
    
            if(root->left == nullptr && root->right == nullptr)
            {
                // 叶子节点
                // 新增一条路径
                ret.push_back(std::to_string(root->val));
                return std::make_pair(ret.size() - 1, ret.size() - 1);
            }
            else
            {
                // 支节点
                // 在原来的上添加
                for(int i = (l_area.first == -1 ? r_area.first : l_area.first);i <= (r_area.second == -1 ? l_area.second : r_area.second);i++)
                {
                    std::string tmp = std::to_string(root->val) + link_flag + ret[i];
                    ret[i] = std::move(tmp);
                }
    
                // 返回新的区间
                return std::make_pair((l_area.first == -1 ? r_area.first : l_area.first),(r_area.second == -1 ? l_area.second : r_area.second));
            }
        }
    
        void test()
        {
            TreeNode* n1 = new TreeNode(5);
            TreeNode* n2 = new TreeNode(2,nullptr,n1);
            TreeNode* n3 = new TreeNode(1,n2,nullptr);
            auto ret = binaryTreePaths(n3);
    
            std::cout << "[" << std::endl;
            
            for(auto& path : ret)
                std::cout << path << std::endl;
            
            std::cout << "]" << std::endl;
        }
    };
    
#endif



#ifdef __VERSION_2.0__

#endif