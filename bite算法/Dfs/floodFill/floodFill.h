// create by hrj
// Current time: 2025-02-22 17:21:19.795
#include "/home/hrj/leetcode/headFile.h"


class Solution {
    int baseColor;
    int m , n;
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    bool used[50][50] = { false };
    void dfs(vector<vector<int>>& image,int row,int col,int color)
    {
        if(row < 0 || row >= m || col < 0 || col >= n || image[row][col] != baseColor || used[row][col]) return;

        image[row][col] = color;
        used[row][col] = true;
        for(int k = 0; k < 4;k++)
            dfs(image,row + dx[k],col + dy[k],color);
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        baseColor = image[sr][sc];
        m = image.size(), n = image[0].size();
        dfs(image,sr,sc,color);
        return image;
    }
};