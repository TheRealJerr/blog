// create by hrj
// Current time: 2025-02-17 23:31:21.695
#include "/home/hrj/leetcode/headFile.h"

class Solution
{
    bool row[9][10] = { false };
    bool col[9][10] = { false };
    bool grid[3][3][10] = { false };
    void setBaseBuffer(vector<vector<char>>& board)
    {
        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
            {
                if(board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
            }
        }
        // 将起始的信息填充好
    }
    bool dfs(vector<vector<char>>& board,int Row,int Col)
    {
        // Debug
        // std::cout << "Row:" << Row << " " << "Col:" << Col << std::endl;
        if(Row == 9) return true;
        if(board[Row][Col] == '.')
        {
            // try
            for(int Try = 1; Try <= 9;Try++)
            {
                // 无效的
                if(row[Row][Try] || col[Col][Try] || grid[Row / 3][Col / 3][Try]) continue;
                
                board[Row][Col] = Try + '0';
                // PrintTable(board);
                row[Row][Try] = col[Col][Try] = grid[Row / 3][Col / 3][Try] = true;
                int nextRow = Row, nextCol = Col + 1;
                if(nextCol == 9){
                    nextRow++;
                    nextCol = 0;
                }
                if(dfs(board,nextRow,nextCol))
                    return true;
                // 回溯
                board[Row][Col] = '.';
                row[Row][Try] = col[Col][Try] = grid[Row / 3][Col / 3][Try] = false;

            }
            return false;
        }
        else
        {
            int nextRow = Row, nextCol = Col + 1;
            if(nextCol == 9){
                nextRow++;
                nextCol = 0;
            }
            return dfs(board,nextRow,nextCol);
        }
    }
 public:
    void solveSudoku(vector<vector<char>>& board)
    {
        // step 1
        setBaseBuffer(board);
        // 递归遍历
        dfs(board,0,0);
    }
    void PrintTable(vector<vector<char>>& board)
    {

        static int count = 0;
        std::cout << "[count]" << ++count << std::endl;
        for(auto& row : board)
        {
            for(auto i : row)
                std::cout << i << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void test()
    {
        vector<vector<string>> tmp = {
            {"5","3",".",".","7",".",".",".","."},
            {"6",".",".","1","9","5",".",".","."},
            {".","9","8",".",".",".",".","6","."},
            {"8",".",".",".","6",".",".",".","3"},
            {"4",".",".","8",".","3",".",".","1"},
            {"7",".",".",".","2",".",".",".","6"},
            {".","6",".",".",".",".","2","8","."},
            {".",".",".","4","1","9",".",".","5"},
            {".",".",".",".","8",".",".","7","9"}
        };
        vector<vector<char>> board;
        board.resize(9,vector<char>(9));
        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
            {
                board[i][j] = tmp[i][j][0];
            }
        }
        solveSudoku(board);
        for(auto& row : board)
        {
            for(auto i : row)
                std::cout << i << ' ';
            std::cout << std::endl;       
        }
    }
};