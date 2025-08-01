#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char,int>> sk;
        int count = 0;
        for(auto ch : s)
        {
            if(!sk.empty() && sk.top().first == ch)
            {
                count = sk.top().second + 1;
                sk.push({ch, count});
            }
            else 
            {
                count = 1;
                sk.push({ch, count});
            }
            
            if(count == k)
            {
                auto tmp = k;
                while(tmp--) sk.pop();
            }
        }
        std::string res;
        res.resize(sk.size());
        auto rit = res.rbegin();
        while(rit != res.rend())
        {
            *rit = sk.top().first;
            sk.pop();
        }
        return res;
    }

    void test()
    {
        std::cout << removeDuplicates("abcd", 2) << std::endl;
    }
};

auto main() -> int
{
    Solution().test();
    return 0;
}