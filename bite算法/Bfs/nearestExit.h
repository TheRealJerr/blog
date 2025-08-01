// create by hrj
// Current time: 2025-03-03 15:59:28.192
#include "/home/hrj/leetcode/headFile.h"


// 迷宫中离入口最近的出口
class Solution {
private:
    using pos_t = std::pair<int,int>;
    int m , n;
    vector<vector<bool>> used; // 记录走过的位置
    void Init(vector<vector<char>>& maze)
    {
        m = maze.size(), n = maze[0].size();
        used.resize(m,vector<bool>(n,false));
    }
    int ret = INT32_MAX; // 出去的最小的步数
    int path = 0; // 当前的步数

    // 定义向量
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };
public:
    
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance)  
    {
        Init(maze);
        // entrance表示我们当前处在的位置
        pos_t begin(entrance[0],entrance[1]);
        std::stack<pos_t> q;
        q.push(begin);
        while(!q.empty())
        {
            auto cur = q.top();
            std::cout << "cur pos:[" << cur.first << "," << cur.second << ']' << std::endl; 
            q.pop();
            // 默认q中的位置都是合法的
            path++;
            // 判断是否是出口
            auto [row , col] = cur;
            used[row][col] = true;
            if(row == 0 || row == m - 1 || col == 0 || col == n - 1)
            {
                // 更新ret
                ret = std::min(ret,path);
            } 
            else 
            {
                for(int k = 0;k < 4;k++)
                {
                    if(row + dx[k] >= 0 && row + dx[k] < m \
                        && col + dy[k] >= 0 && col + dy[k] < n\
                        && !used[row + dx[k]][col + dy[k]] && maze[row + dx[k]][col + dy[k]] == '.')
                        {
                            q.push(std::make_pair(row + dx[k],col + dy[k]));
                        }
                }
            }
            path--; // 回溯
            used[row][col] = false;
        }
        return ret == INT32_MAX ? -1 : ret;
    }
    void test()
    {
        std::vector<vector<char>> maze = 
        {
            { '+' , '+' , '.' , '+'},
            { '.' , '.' , '.' , '+'},
            { '+' , '+' , '+' , '.'},
        };
        std::vector<int> entrance = { 1 , 2 };
        auto tmp = nearestExit(maze,entrance);
        std::cout << tmp << std::endl;
    }
};