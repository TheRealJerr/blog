//
// Created by jerry on 2024/9/7.
//
//leetcode 974 . 可被k整除的子数组
#include "headFile.h"
#ifndef LEETCODE_SUBARRAYSDIVBYK_H
#define LEETCODE_SUBARRAYSDIVBYK_H

//这道题目的思路也是,利用前缀和
///通过remd记录加到现在为止mod k = ?
///然后利用前面记录的hash表去查找,原理就是hashtable中记录当前之前的所有位置mod k 的值
//细节
//1.hash[0] = 1 由于没有时默认mod 后为0
///2.如果说,remd < 0的时候remd += k这一步很关键,因为mod的值不一定是正数,也可能是 > -k < 0 的负数
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int,int> hash;
    int remd = 0, count = 0;
    hash[0] = 1;
    for(auto e : nums){
        remd = (remd + e) % k;
        if(remd < 0) remd += k;
        cout << e << " " << remd << " " << hash[remd] << endl;
        count += (hash[remd]++);

    }
    return count;
}
#endif //LEETCODE_SUBARRAYSDIVBYK_H
