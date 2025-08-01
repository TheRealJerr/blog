// create by hrj
// Current time: 2025-02-22 20:35:06.101
#include "/home/hrj/leetcode/headFile.h"

class Solution {
private:
    int m,n;
    int ret = 0;
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
    vector<vector<bool>> used;
    int dfs(vector<vector<int>>& grid,int row,int col)
    {
        if(row < 0 || row >= m || col < 0 || col >= n || !grid[row][col] || used[row][col])
            return 0;
        int sum = 1;
        used[row][col] = true;
        for(int k = 0;k < 4;k++)
            sum += dfs(grid,row + dx[k],col + dy[k]);
        return sum;
    }
public:

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        // 岛屿的最大面积
        m = grid.size(), n = grid[0].size();
        used.resize(m,vector<bool>(n,false));
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(!used[i][j] && grid[i][j])
                {
                    auto landsize = dfs(grid,i,j);
                    ret = std::max(ret,landsize);
                }
            }
        }
        return ret;
    }
};