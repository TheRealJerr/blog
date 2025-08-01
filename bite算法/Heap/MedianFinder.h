// create by hrj
// Current time: 2025-03-01 19:52:18.686
#include "/home/hrj/leetcode/headFile.h"

class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // 这里我们规定low.size() >= up.size();
        int l = low.empty() == true ? INT32_MAX : low.top();
        // int r = up.empty() == true ? (-INT32_MAX) : up.top();
        if(num < l) low.push(num);
        else up.push(num);

        // 平衡一下
        // 这里有一个隐藏的大坑,就是low.size()和up.size()的类型都是size_t的容易变成INT_MAX
        int tmp = low.size() - up.size();
        if(tmp >= 2)
        {
            up.push(low.top());
            low.pop();
        }else if(tmp < 0)
        {
            low.push(up.top());
            up.pop();
        }
    }
    
    double findMedian() {
        if(low.size() == up.size()) return ((double)low.top() + (double)up.top()) / 2;
        else return (double) low.top(); 
    }

    void test()
    {
        addNum(1);
        addNum(2);
        addNum(3);
        std::cout << findMedian() << std::endl;
    }
    std::priority_queue<int,std::vector<int>,std::less<int>> low;
    std::priority_queue<int,std::vector<int>,std::greater<int>> up;
    // 总共n个数
    // [n / 2] 构建的小的那一边的大堆
    // [n / 2] 构建大的那一边的小堆
};

