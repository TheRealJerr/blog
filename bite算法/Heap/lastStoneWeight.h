// create by hrj
// Current time: 2025-03-01 19:17:22.748
#include "/home/hrj/leetcode/headFile.h"

// 最后一块石头的重量

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> pq(stones.begin(), stones.end());

        while(pq.size() >= 2)
        {
            int l = pq.top(); pq.pop();
            int r = pq.top(); pq.pop();
            if(l != r) pq.push(l > r ? l - r : r - l);
        }
        return pq.size() == 1 ? pq.top() : 0;
    }
};