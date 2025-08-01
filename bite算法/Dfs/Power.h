
#ifdef __NEWCODER__
// 牛客网的代码
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

using ll = long long int; // c++11

// 这道题的思想就是归并加动态规划时间复杂度为log(n)
// std::vector<ll> buffer;
// 缓冲区承受不住
// 那就只有用哈希了
std::unordered_map<int,ll> dp;

ll Dfs(ll a,ll b,ll p)
{
    if(b == 0) return 1;
    else if(b == 1) return a % p;
    if(dp.count(b)) return dp[b]; // a ^ b  mod p
    // 通过缓冲区加快速录
    // 拆分
    ll left = b / 2;
    ll right = b - left;
    ll l = Dfs(a,left,p);
    ll r = Dfs(a,right,p);
    ll ret = (l * r) % p;
    dp[b] = ret;
    return ret;
}
void handerRequest()
{
    ll a = 0, b = 0, p = 0;
    std::cin >> a >> b >> p;
    // a^b mod p
    // 清楚之前的数据
    dp.clear();
    a %= p;
    // 通过递归利用归并
    std::cout << Dfs(a,b,p) << std::endl;
}
#endif