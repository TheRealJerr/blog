//
// Created by jerry on 2024/9/8.
//
//leetcode 1314 矩阵区域和
#include "headFile.h"
#ifndef LEETCODE_MATRIXBLOCKSUM_H
#define LEETCODE_MATRIXBLOCKSUM_H
vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    vector<vector<int>> prefix(mat.size() + 1,vector<int>(mat[0].size() + 1, 0));
    vector<vector<int>> ret(mat.size(),vector<int>(mat[0].size(), 0));
    //建立一个目标的二维矩阵
    int lines = mat.size();
    int cols = mat[0].size();
    for(int i = 1;i <= lines;i++){
        for(int j = 1;j <= cols;j++){
            if(i == 1 && j == 1) prefix[i][j] = mat[0][0];
            else if(i == 1) prefix[i][j] = prefix[i][j - 1] + mat[i - 1][j - 1];
            else if(j == 1) prefix[i][j] = prefix[i - 1][j] + mat[i - 1][j - 1];
            else prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mat[i - 1][j - 1];
        }
    }
    for(int i = 0;i < lines;i++){
        for(int j = 0;j < cols;j++){
            int x1 = (i - k) < 0 ? 0 : (i - k);
            int y1 = (j - k) < 0 ? 0 : (j - k);
            int x2 = (i + k) >= lines ? lines - 1: (i + k);
            int y2 = (j + k) >= cols ? cols - 1: (j + k);
            ret[i][j] = prefix[x2 + 1][y2 + 1] - prefix[x1][y2 + 1] - prefix[x2 + 1][y1] + prefix[x1][y1];
        }
    }
    return ret;
}
void test()
{
    vector<vector<int>> mat;
    mat.push_back({67,64,78});
    mat.push_back({99,98,38});
    mat.push_back({82,46,46});
    mat.push_back({6,52,55});
    mat.push_back({55,99,45});
    vector<vector<int>> ret = matrixBlockSum(mat,1);
    for(auto& e : ret)
        for(auto i : e)
            cout << i << " ";
    cout << endl;
}
#endif //LEETCODE_MATRIXBLOCKSUM_H
