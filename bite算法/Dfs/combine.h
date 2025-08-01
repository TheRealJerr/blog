// create by hrj
// 2025-02-11 10:39:28.122

#include "../headFile.h"

class Solution
{
    vector<int> path;
    vector<vector<int>> ret;
public:
    void dfs(int pos, int n, int k)
    {
        if(path.size() == k) ret.push_back(path);

        for(int i = pos; i <= n; i++)
        {
            path.push_back(i);
            dfs(i + 1,n,k);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n,int k)
    {
        dfs(1,n,k);
        return ret;
    }
    void test()
    {
        auto ret = combine(4,2);
        for(auto & arr : ret)
        {
            std::cout << "[";
            for(auto e : arr) std::cout << e << " ";
            std::cout << "]" << std::endl;
        }

    }
};

