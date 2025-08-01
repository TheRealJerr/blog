//
// Created by jerry on 2024/10/6.
//
#include "headFile.h"
#ifndef LEETCODE_COUNTANDSAY_H
#define LEETCODE_COUNTANDSAY_H
string countAndSay(int n) {
    if(n == 1) return "1";
    string ret = countAndSay(n - 1);
    string cur;
    int count = 0;
    for(int left = 0, right = 0;right < ret.size();right++){

        if(ret[right] == ret[left]) count++;
        else{
            cur += to_string(count);
            cur += ret[left];
            count = 1;
            left = right;
        }
        //如果说right到了尾部,我们还是要进行清算
        if(right == ret.size() - 1){
            cur += to_string(count);
            cur += ret[right];
        }
    }
    return cur;
}
void test()
{
    std::cout << countAndSay(4) << std::endl;
}
#endif //LEETCODE_COUNTANDSAY_H
