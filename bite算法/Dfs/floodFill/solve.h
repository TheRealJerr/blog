// create by hrj
// Current time: 2025-02-22 20:47:49.460
#include "/home/hrj/leetcode/headFile.h"

#define __VERSION_2.0___
#ifdef __VERSION_1.0___
class Solution {
private:
    int m,n;
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
    vector<vector<bool>> used;
    bool dfs(vector<vector<char>>& board,int row,int col,bool flag)
    {
        // 边界情况
        if(row < 0 || row >= m || col < 0 || col >= n || board[row][col] == false || used[row][col]) return false;
        if(flag)
        {
            // 上层已经出现了边界点
            board[row][col] = 'X';
            used[row][col] = true;
            for(int k = 0;k < 4;k++)
                dfs(board,row + dx[k],col + dy[k],true);
            return true;
        }
        else 
        {
            // 边界点
            if(row == 0 || row == m - 1 || col == 0 || col == n - 1)
            {
                board[row][col] = 'X';
                used[row][col] = true;
                for(int k = 0;k < 4;k++)
                dfs(board,row + dx[k],col + dy[k],true);
                return true;
            }
            else
            {
                // 先看dfs有没有边界点
                bool tmp = false;
                for(int k = 0;k < 4;k++)
                {
                    if(dfs(board,row + dx[k],col + dy[k],false)) tmp = true;
                }
                if(tmp)
                {
                    // 下层出现边界点
                    board[row][col] = 'X';
                    used[row][col];
                    // 重新修改
                    for(int k = 0;k < 4;k++)
                        dfs(board,row + dx[k],col + dy[k],true);
                    return true;
                }
                // 没有
                return false;
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        // 被围绕的区域
        m = board.size(), n = board[0].size();
        used.resize(m,vector<bool>(n,false));
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(!used[i][j] && board[i][j] == 'O')
                    dfs(board,i,j,false);
            }
        }
    }
};
#endif


#ifdef __VERSION_2.0__
class Solution
{
    int m , n;
    vector<vector<bool>> grid;
    // 设置向量
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
    void sign(vector<vector<char>>& board,int row,int col)
    {
        // 将不需要将O->X的区域标记
        if(row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == true || board[row][col] == 'X') return;
        grid[row][col] = true;
        // 这些事不需要变得
        for(int k = 0;k < 4;k++)
            sign(board,row + dx[k],col + dy[k]);
    }

    void set(vector<vector<char>>& board,int row,int col)
    {
        if(row < 0 || row >= m || col < 0 || col >= n || board[row][col] == 'X') return;
        board[row][col] = 'X';
        for(int k = 0;k < 4;k++)
            set(board,row + dx[k],col + dy[k]); 
    }
public:
    void solve(vector<vector<char>>& board)
    {
        // 将不需要将O->X的区域标记
        m = board.size(), n = board[0].size();
        grid.resize(m,vector<bool>(n,false));
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(board[i][j] == 'O' && (i == 0 || i == m - 1 || j == 0 || j == n - 1) && grid[i][j] == false)
                    sign(board,i,j);
            }
        }
        // 将没有标记的区域的O->X
        for(int i = 0;i < m;i++)
        {
            for(int j = 0;j < n;j++)
            {
                // 没有标记的染色
            
                if(board[i][j] == 'O' && !grid[i][j]) set(board,i,j);
        
            }
        }
    }
    void test()
    {
        vector<vector<char>> board = 
        {
            { 'X' ,'X' ,'X', 'X'},
            { 'X' ,'O' ,'O', 'X'},
            { 'X' ,'X' ,'O', 'X'},
            { 'X' ,'O' ,'X', 'X'},
        };
        solve(board);
        for(auto& row : board)
        {
            for(auto e : row)
                std::cout << e << " ";
            std::cout << std::endl;
        }
    }
};
#endif