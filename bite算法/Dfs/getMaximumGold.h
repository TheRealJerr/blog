// create by hrj
// Current time: 2025-02-22 15:19:31.369
#include "/home/hrj/leetcode/headFile.h"

class Solution {
private:
    int ret = -1;
    int m,n;
    int Sum = 0; // 总的收益
    bool used[15][15] = { false }; // 每个矿的使用的情况
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
    void dfs(vector<vector<int>>& grid,int row,int col)
    {
        if(row < 0 || row >= m || col < 0 || col >= n || used[row][col] || grid[row][col] == 0)
        {
            // 更新ret;
            ret = std::max(ret,Sum);
            return;
        }
        used[row][col] = true;
        Sum += grid[row][col];
        for(int k = 0;k < 4;k++)
        {
            dfs(grid,row + dx[k],col + dy[k]);
        }
        Sum -= grid[row][col];
        used[row][col] = false;
    }
public:

    int getMaximumGold(vector<vector<int>>& grid) {
        // 黄金矿工
        m = (int)grid.size();
        n = (int)grid[0].size();
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(grid[i][j]) dfs(grid,i,j); // 入口
            }
        }
        return ret == -1 ? 0 : ret;    
    }
};