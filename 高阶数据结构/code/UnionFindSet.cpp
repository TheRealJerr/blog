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
        // 优化, 优先将小的合并进入大的集合
        if(root_x1 > root_x2)
            std::swap(root_x1, root_x2);
        if(root_x1 != root_x2)
        {
            _ufs[root_x1] += _ufs[root_x2];
            _ufs[root_x2] = root_x1;
        }        
        
    }
    // 获取根
    // 优化，我们可以在findRoot进行路径合并
    int findRoot(int x) 
    {
        auto tmp = x;
        while(_ufs[tmp] >= 0) tmp = _ufs[tmp];

        auto t = x;
        while(t != tmp)
        {
            int s = t;
            t = _ufs[t];
            _ufs[s] = tmp;
        }
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