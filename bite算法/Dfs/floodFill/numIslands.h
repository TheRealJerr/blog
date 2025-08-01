// create by hrj
// Current time: 2025-02-22 18:32:42.723
#include "/home/hrj/leetcode/headFile.h"

class Solution {
    int count = 0; // 计数器
    int m , n;
    vector<vector<int>> used;
public:

    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
    void dfs(vector<vector<char>>& grid,int row,int col)
    {
        if(row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == '0' || used[row][col]) return;
        used[row][col] = 1;
        for(int k = 0;k < 4;k++)
            dfs(grid,row + dx[k],col + dy[k]);
    }

    int numIslands(vector<vector<char>>& grid) {
        // 岛屿数量
        // floodfill算法
        m = (int)grid.size(), n = (int)grid[0].size();
        used.resize(m,vector<int>(n,0));
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(grid[i][j] == '1' && !used[i][j]){
                    dfs(grid,i,j);
                    ++count;
                }
            }
        }
        return count;
    }
};