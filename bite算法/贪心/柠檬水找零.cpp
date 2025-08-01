/*
分情况讨论
1. 5 -> 直接收下
2. 10 -> 找五块钱
3. 15 -> 1. 如果可以找10 + 5, 没有十块钱, 找三张五块钱
*/

#include "../headFile.h"

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) 
    {
        // 
        int five_size = 0, ten_size = 0, twenty_size = 0;
        for(auto i : bills)
        {
            if(i == 5) five_size++;
            else if(i == 10) 
            {
                ten_size++;
                if(five_size-- == 0) return false;
            }
            else 
            {
                // 20
                twenty_size++;
                if(ten_size > 0)
                {
                    ten_size--;
                    if(five_size-- == 0) return false;
                }
                else 
                {
                    if(five_size < 3) return false;
                    five_size -= 3;
                }
            }
        }    
        return true;
    }
};