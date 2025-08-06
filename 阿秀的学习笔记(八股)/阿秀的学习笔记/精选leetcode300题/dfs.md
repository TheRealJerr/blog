# dfs模块

## **39. 组合总和**

[leetcode](https://leetcode.cn/problems/combination-sum/description/)

给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。

 

示例 1：

输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。
示例 2：

输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
示例 3：

输入: candidates = [2], target = 1
输出: []

```cpp
class Solution {

    int _target;
    vector<int> path;
    vector<vector<int>> res;
    int sum = 0;
public: 
    void dfs(vector<int>& array,int pos)
    {   
        if(pos == array.size()) return;
        // 从0个到n个
        // 方便进行回溯
        auto before = sum;
        auto before_size = path.size();
        while(sum <= _target)
        {
            if(sum == _target) 
            {
                res.push_back(path);
                break;
            }
            else dfs(array,pos + 1);
            sum += array[pos];
            path.push_back(array[pos]);
        }
        // 进行回溯
        sum = before;
        while(path.size() > before_size) path.pop_back();
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        _target = target;
        dfs(candidates, 0);
        return res;
    }
};
```

## 46. 全排列

给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

 

示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]

```cpp
class Solution {
    vector<vector<int>> res;
    vector<bool> used;
    int n;
    vector<int> path;
public:
    void dfs(vector<int>& nums, int pos)
    {
        if(pos == n) res.push_back(path);
        for(int i = 0;i < n;i++)
        {
            if(used[i] == false)
            {
                used[i] = true;
                path[pos] = nums[i];
                dfs(nums,pos + 1);
                used[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) 
    {
        n = nums.size();
        used.resize(n, false);
        path.resize(n, 0);
        dfs(nums,0);
        return res;
    }
};
```

