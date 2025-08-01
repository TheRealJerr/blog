// create by hrj
// 2025-02-11 10:53:21.127

// n 皇后问题
#include "../headFile.h"

#ifdef __VERSION_1.0__

#include "../headFile.h"

class Solution
{
    vector<vector<string>> ret;
    vector<string> path;
    std::string getPosString(int pos,int n)
    {
        std::string tmp;
        for(int i = 1; i <= n;i++)
        { 
            if(i == pos) tmp.push_back('Q');
            else tmp.push_back('.');
        }
        return tmp;
    }
public:
    void dfs(int last,int n)
    {
        if(path.size() == n) 
        {
            ret.push_back(path);
            return;
        }
        // 本质就是通过上一个皇后的位置进行爆搜
        // 1 ~ last - 2
        // last + 2 ~ n
        for(int i = 1;i <= last - 2;i++)
        {
            path.push_back(getPosString(i,n));
            dfs(i,n);
        }
        for(int i = last + 2;i <= n;i++)
        {

        }

    }
    vector<vector<string>> solveNQueens(int n)
    {

    }
};
#endif
#define __VERSION_2.0__

#ifdef __VERSION_2.0__
class Solution
{
private:
    vector<vector<int>> form;
    vector<vector<string>> ret;
    vector<string> path;
    void setTable(int i, int j, int n)
    {
        for(int cur = j + 1; cur <= n; cur++)
        {
            if(cur - j + 1 <= i) form[i - (cur - j)][cur]++;
            form[i][cur]++;
            if(i + (cur - j) <= n) form[i + (cur - j)][cur]++;
        }

    }
    void recallTable(int i, int j, int n)
    {
        for(int cur = j + 1; cur <= n; cur++)
        {
            if(cur - j + 1 <= i) form[i - (cur - j)][cur]--;
            form[i][cur]--;
            if(i + (cur - j) <= n) form[i + (cur - j)][cur]--;
        }
    }   
    std::string getPathString(int pos, int n)
    {
        string tmp;
        for(int i = 1; i <= n; i++)
        {
            if(i == pos) tmp.push_back('Q');
            else tmp.push_back('.'); 
        }
        return tmp;
    }
public:
    void printTable(int n)
    {
        static int count = 0;
        std::cout << "[Table count]" << ++count << std::endl;
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1; j <= n; j++)
                std::cout << form[i][j] << " ";
            std::cout << std::endl;
        }
    }
    void dfs(int j, int n)
    {
        if(path.size() == n) {
            ret.push_back(path);
            return;
        }
        for(int i = 1; i <= n; i++)
        {
            
            if(form[i][j]) continue;// 剪枝

            form[i][j] = 1;
            path.push_back(getPathString(i,n));
            setTable(i,j,n);
            dfs(j + 1,n);
            recallTable(i,j,n);
            form[i][j] = 0;
           
            path.pop_back();
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        form.resize(n + 1,vector<int>(n + 1,0));
        dfs(1,n);
        return ret;
    }
    void test()
    {
        auto ret = solveNQueens(4);
        int count = 0;
        for(auto& tmp : ret)
        {
            std::cout << "[size]" << ++count << std::endl;
            for(auto& str : tmp)
                std::cout << str << std::endl;
                
        }
    }
};
#endif