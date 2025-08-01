//
// Created by jerry on 2024/8/24.
//
#include "headFile.h";
#ifndef LEETCODE_MINSUBARRAYLEN_H
#define LEETCODE_MINSUBARRAYLEN_H
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0;
    int right = 0;
    int size = nums.size();
    int sum = 0;
    int gap = 0;
    bool flag = false;
    while(right < size)
    {
        while(sum < target && right < size)
        {
            sum+=nums[right++];
        }
        if(sum >= target && flag == false) {
            flag = true;
            gap = right - left;
        }
        else if(sum >= target && flag == true) {
            if(gap > right - left) gap = right - left;
        }
        sum-=nums[left++];
    }
    return gap;
}
int minSubArrayLen2(int target, vector<int>& nums) {
    int Min = INT_MAX;
    int sum = 0;
    for(int left = 0,right = 0;right < nums.size();right++)
    {
        //进入窗口
        sum += nums[right];
        if(sum >= target){
            while(sum >= target)
                sum -= nums[left++];
            sum += nums[--left];
            Min = std::min(Min,right - left + 1);
        }

    }
    if(Min == INT_MAX) Min = 0;
    return Min;
}
void test()
{
    vector<int> arr= {1,2,3,4,5};
    int ret = minSubArrayLen2(11,arr);
    cout << ret << endl;
}

#endif //LEETCODE_MINSUBARRAYLEN_H
