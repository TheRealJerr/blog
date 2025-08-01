# 双指针 [day1]

## 1. 移动零

[移动零](https://leetcode.cn/problems/move-zeroes/description/)


给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。


**解法**

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int before_zero_size = 0;
        for(int i = 0;i < nums.size();i++)
        {
            if(nums[i] == 0) before_zero_size++;
            else if(before_zero_size > 0) nums[i - before_zero_size] = nums[i];
        }
        // 从后往前填充 
        for(int end = nums.size() - 1; end > nums.size() - 1 - before_zero_size;end--)
            nums[end] = 0;
        
    }
};
```

## 2. 复写零

[复写零](https://leetcode.cn/problems/duplicate-zeros/description/?page=1)

给你一个长度固定的整数数组 arr ，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。

注意：请不要在超过该数组长度的位置写入元素。请对输入的数组 就地 进行上述修改，不要从函数返回任何东西。

**思路**

`这道题的核心就是从后往前遍历`

对于这一类问题，包括上面的移动零, 其实本质上都是确定好复写后, 每个元素的结果的位置，由于我们的元素复写后应该往后移动，所以我们应该从后往前遍历，但是为了确定最后的位置，我们还需要首先得到零的总个数`size`


```cpp
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        // 注意不要越界
        int n = arr.size();
        int zero_size = 0;
        for(auto x : arr) 
            if(x == 0) ++zero_size;
        //
        int back_zero_size = 0;
        for(int cur = n - 1; cur >= 0; cur--)
        {
            if(arr[cur] == 0)
            {
                back_zero_size++;
                int front_zero_size = zero_size - back_zero_size;
                if(front_zero_size + cur < n) arr[cur + front_zero_size] = 0;
                if(front_zero_size + cur + 1 < n) arr[cur + front_zero_size + 1] = 0;
            }
            else if(cur + zero_size - back_zero_size < n) 
                arr[cur + zero_size - back_zero_size] = arr[cur];
        } 
    }
};
```

## 