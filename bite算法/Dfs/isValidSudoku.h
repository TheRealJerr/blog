// create by hrj
// Current time: 2025-02-17 16:48:13.165
#include "/home/hrj/leetcode/headFile.h"
// 解数独

// 规则
// 每行 / 每列 / 每个3 * 3的方格中1 ~ 9只能出现一次
#ifdef __VERSION_1.0__
class Solution {
    // 通过hash的思想进行缓存
    
    bool checkCol[9][10] = { false };
    bool checkRow[9][10] = { false };
    bool checkGroup[3][3][10] = { false };
    void dfs(int row, vector<vector<char>>& board)
    {
        for(int col = 0; col < board[row].size(); col++)
        {
            if(board[row][col] != '.') continue;
            for(int choi = 1; choi <= 9; choi++)
            {
                if(!checkCol[col][choi] && !checkRow[row][choi] && !checkGroup[row / 3][col / 3][choi])
                {
                    board[row][col] = choi + '0';
                    checkCol[col][choi] = true;
                    checkRow[row][choi] = true;
                    checkGroup[row / 3][col / 3][choi] = true;
                }
            }
        }
    }
    void setDefaultInfo(vector<vector<char>>& board)
    {
        for(int row = 0; row < board.size(); row++)
        {
            for(int col = 0; col < board[row].size(); col++)
            {
                int tmp = board[row][col] - '0';
                if(board[row][col] == '.') continue;
                checkCol[col][tmp] = true;
                checkRow[row][tmp] = true;
                checkGroup[row / 3][col / 3][tmp] = true;
            }
        }
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) 
    {

    }
};
#endif

#define __VERSION_2.0__
#ifdef __VERSION_2.0__
class Solution
{
    bool row[9][10] = { false };
    bool col[9][10] = { false };
    bool grid[3][3][10] = { false };
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
            {
                if(board[i][j] != '.')
                {
                    // 是否是有效的
                    int num = board[i][j] = '0';
                    if(row[i][num] || col[j][num] || grid[i / 3][j / 3][num])
                        return false;
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }
            }
        }
        return true;
    }
};
#endif