// create by hrj
// Current time: 2025-02-25 15:07:04.189
#include "/home/hrj/leetcode/headFile.h"
class Solution
{
    using ll = long long int;
    int CNX(int all,int x)
    {
        long long ret = 1;
        int count1 = 0, count2 = 1;
        for(count1 = 0;count1 < x;count1++)
        {
            ret *= (all - count1);
            while(count2 <= x)
            {
                if(ret % count2 == 0) ret /= count2++;
                else break;
            }
            
        }
        return ret;
    }
public:
    int uniquePaths(int m,int n)
    {
        m--,n--;
        return CNX(m + n,std::min(m,n));
    }
    void test()
    {
        std::cout << uniquePaths(3,2) << std::endl;
        std::cout << uniquePaths(4,2) << std::endl;
    }
};