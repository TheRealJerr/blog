#include <iostream>
#include <vector>

// 没有路径压缩的简单的并查集
// 通过这个题目我们可以解决朋友圈的问题

class UnionFindSet
{
public:

    UnionFindSet(size_t n) : _ufs(n, -1)
    {}

    // 合并两个并查集
    void Union(int x1, int x2)
    {
        // 找到两个数的根
        int root_x1 = findRoot(x1);
        int root_x2 = findRoot(x2);
        // 合并两个根
        if(root_x1 != root_x2)
        {
            _ufs[root_x1] += _ufs[root_x2];
            _ufs[root_x2] = root_x1;
        }        
        
    }
    // 获取根
    int findRoot(int x) const
    {
        auto tmp = x;
        while(_ufs[tmp] >= 0) tmp = _ufs[tmp];

        return tmp; 
    }
    // 是否在一个集合里面
    bool isInOneSet(int x1, int x2)
    {
        return findRoot(x1) == findRoot(x2);
    }

    size_t setSize(int x) const 
    {
        size_t count = 0;
        for(auto val : _ufs)
            if(val < 0) count++;
        return count;
    }
private:

    std::vector<int> _ufs;
};