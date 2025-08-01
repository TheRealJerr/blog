// create by hrj
// Current time: 2025-02-24 18:57:55.366
#include "/home/hrj/leetcode/headFile.h"

// 太平洋大西洋水流问题
class Solution
{
    // 向量
    int dx[4] = { 0 , 0 , 1 , -1 };
    int dy[4] = { 1 , -1 , 0 , 0 };

    using board_t = vector<vector<int>>;
    vector<vector<bool>> used;
    int m, n;
    vector<vector<std::pair<bool,bool>>> status;
    // 返回值
    vector<vector<int>> ret;
public:
    // 通过深度优先遍历
    // 返回值表示(是否流入太平洋)(是否流入大西洋)
    std::pair<bool,bool> dfs(board_t& heights,int row,int col)
    {
        // 越界 // 这里无所谓，因为根本用不上
        if(row < 0 || row >= m || col < 0 || col >= n) return std::make_pair(false,false);
        // 重复的位置
        if(used[row][col]) return status[row][col];
        // 全新的位置
        used[row][col] = true;
        std::pair<bool,bool> tmp;
        if(row == 0 || col == 0) tmp.first = true; // 连接太平洋
        if(row == m - 1 || col == n - 1) tmp.second = true; // 连接大西洋
        if(tmp.first == true && tmp.second == true)
        {
            ret.push_back({row,col});
            status[row][col] = tmp;
            return tmp;
        }
       
        // bug这里先调用子可能引起无穷递归

        for(int k = 0;k < 4;k++)
        {
            auto st = dfs(heights,row + dx[k],col + dy[k]);
            if(st.first && heights[row][col] >= heights[row + dx[k]][col + dy[k]]) tmp.first = true;
            if(st.second && heights[row][col] >= heights[row + dx[k]][col + dy[k]]) tmp.second = true;
        }
        if(tmp.first == true && tmp.second == true) ret.push_back({ row,col });
        status[row][col] = tmp;
        return tmp;
    }
    void Init(board_t& heights)
    {
        m = heights.size(), n = heights[0].size();
        used.resize(m,vector<bool>(n,false)); // 初始化时所有位置没有使用
        status.resize(m,vector<std::pair<bool,bool>>(n,{false,false}));
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // 定义一个used列表，表示已经计算过的区域，避免重复计算
        Init(heights);
        dfs(heights,0,0);
        return ret;
    }
    void test()
    {
        vector<vector<int>> heights = 
        {
            { 1,2,2,3,5 }, 
            { 3,2,3,4,4 },
            { 2,4,5,3,1 },
            { 6,7,1,4,5 },
            { 5,1,1,2,4 },
        };
        auto t = pacificAtlantic(heights);
        for(auto& pair : t)
        {
            for(auto e : pair)
                std::cout << e << " ";
            std::cout << std::endl;
        }
    }
};