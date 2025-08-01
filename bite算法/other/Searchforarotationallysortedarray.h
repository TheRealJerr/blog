//
// Created by jerry on 2024/8/29.
//
#include "headFile.h"
#ifndef LEETCODE_SEARCHFORAROTATIONALLYSORTEDARRAY_H
#define LEETCODE_SEARCHFORAROTATIONALLYSORTEDARRAY_H
int search(vector<int>& nums, int target) {
    //首先我们需要通过二分查找找到分界点
    int left = 0, right = nums.size() - 1;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(nums[mid] > nums.back()) left = mid + 1;
        else right = mid;
    }
    int pos = 0;
    pos = left;
    //找到分界点
    if(nums[pos] > target) return -1;
    else if(pos && target > nums[pos - 1]) return -1;
    left = 0, right = nums.size() - 1;
    while(left < right)
    {
        int mid = left + (right - left) / 2;
        int tmp = mid;
        mid = (mid + pos) % nums.size();
        if(nums[mid] < target) left = tmp + 1;
        else right = tmp;
    }
    int realPos = (left + pos) % nums.size();
    if(nums[realPos] == target) return realPos;
    else return -1;
}
void test()
{
    vector<int> arr({1,3,5});
    int ret = search(arr,3);
    cout << ret << endl;
}

#endif //LEETCODE_SEARCHFORAROTATIONALLYSORTEDARRAY_H
