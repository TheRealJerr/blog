// 训练士兵
#include <iostream>
#include <queue>
#include <vector>

using std::priority_queue;
using std::vector;
using Pair = std::pair<int,int>;

struct Cmp
{
    bool operator()(const Pair& l,const Pair& r) const 
    {
        return l.first < r.first;
    }
};

void Init(vector<std::pair<int,int>>& Acount,int& n,int& All)
{
    std::cin >> n >> All;
    Acount.resize(n);
    // 默认first 的次数,second的钱
    for(auto& one : Acount)
        std::cin >> one.first >> one.second;
}

void process()
{
    // 初始化
    vector<std::pair<int,int>> Acount;
    int n = 0, All = 0;
    Init(Acount,n,All);
    // 初始化priority_queue
    priority_queue<Pair,vector<Pair>,Cmp> pq;
    for(auto& solder : Acount)
        pq.push(solder);
    
       
}

int main()
{
    process();
    return 0;
}