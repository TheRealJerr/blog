//
// Created by jerry on 2024/10/8.
//
#include "headFile.h"
#ifndef LEETCODE_FINDKTHLARGEST_H
#define LEETCODE_FINDKTHLARGEST_H
void AjustDown(vector<int>& nums,int parent,int size)
{
    int child = 2 * parent + 1;
    while(child < size){
        if(child + 1 < size && nums[child + 1] < nums[child]) child++;
        if(nums[parent] > nums[child]) std::swap(nums[parent],nums[child]);
        else break;
        parent = child;
        child = 2 * child + 1;
    }
}
int findKthLargest(vector<int>& nums, int k) {
    //这里我们使用向下建堆的方式建立一个k大的小堆的结构
    for(int end = (k - 2) / 2;end >= 0;end--)
        AjustDown(nums,end,k);//k * log k 的时间复杂度
    for(int cur = k;cur < nums.size();cur++)
    {
        if(nums[cur] > nums[0]){
            std::swap(nums[cur],nums[0]);
            AjustDown(nums,0,k);
        }
    }
    return nums[0];
}
void test(){
    vector<int> arr = {3,2,1,5,6,4};
    cout << findKthLargest(arr,2);
}
#endif //LEETCODE_FINDKTHLARGEST_H
