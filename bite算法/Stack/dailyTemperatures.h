#include "../headFile.h"

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        // 这里使用单调栈的算法
        std::stack<int> sk;
        std::vector<int> ret(t.size());
        int n = t.size();
        for(int i = 0;i < n;i++)
        {
            int cur = t[i];
            while(sk.size() && cur > t[sk.top()])
            {
                auto pos = sk.top(); sk.pop();
                ret[pos] = i - pos;
            }
            
            sk.push(i);
        }
        // 最终单调栈中剩余的下标都是右边没有大于数据
        while(sk.size())
        {
            ret[sk.top()] = 0;
            sk.pop(); 
        }
        return ret;
    }
};