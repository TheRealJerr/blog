// create by hrj
// Current time: 2025-02-19 11:39:00.858
#include "/home/hrj/leetcode/headFile.h"
// 单词搜索
enum
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
}
class Solution
{
    bool used[6][6] = { false }; // 标记一个位置是否使用过
    
public:
    Solution()
    {
        for(int i = 0;i < 6;i++)
        {
            for(int j = 0;j < 6;j++)
                used[i][j] = false;
        }
    }
    bool dfs(vector<vector<char>>& board,const string& word,int pos,int row,int col)
    {
        if(pos == word.size()) return true;
        // 越界
        if(row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) {
            return false;
        }
        // 不对或者使用过了
        if(used[row][col] || board[row][col] != word[pos]){
           
            return false;
        }
        // 上下左右
        used[row][col] = true;
        bool ret = (dfs(board,word,pos + 1,row + 1,col) || dfs(board,word,pos + 1,row - 1,col) || dfs(board,word,pos + 1,row,col + 1)\
            || dfs(board,word,pos + 1,row,col - 1));
        used[row][col] = false;
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) 
    {
        for(int i = 0;i < board.size();i++)
        {
            for(int j = 0; j < board[i].size();j++)
            {
                if(board[i][j] == word[0])
                {
                    used[i][j] = true;
                    if(dfs(board,word,1,i + 1,j) || dfs(board,word,1,i - 1,j) \
                || dfs(board,word,1,i,j + 1) || dfs(board,word,1,i,j - 1)) 
                        return true;
                    used[i][j] = false; // 回复现场

                }
            }
        }
    }
    void test()
    {
        vector<vector<char>> board = 
        {
            {'A','B','C','E'},
            {'S','F','C','S'},
            {'A','D','E','E'},
        };
        bool ret = exist(board,"ABCCED");
        if(ret) 
            std::cout << "True" << std::endl;
        else 
            std::cout << "False" << std::endl;
    }
};