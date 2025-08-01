//
// Created by jerry on 2024/9/6.
//
#include "headFile.h"
#ifndef LEETCODE_TWOPREFIX_H
#define LEETCODE_TWOPREFIX_H
void twoPrefix()
{
    int lines = 0, cols = 0, n = 0;
    cin >> lines >> cols >> n;
    vector<vector<long long int>> prim(lines + 1,vector<long long int>(cols + 1,0));
    vector<vector<long long int>> dp(lines + 1,vector<long long int>(cols + 1,0));
    for(int _lines = 1;_lines <= lines;_lines++)
        for(int _cols = 1;_cols <= cols;_cols++)
            cin >> prim[_lines][_cols];
    for(int _lines = 1;_lines <= lines;_lines++)
        for(int _cols = 1;_cols <= cols;_cols++)
            dp[_lines][_cols] = dp[_lines - 1][_cols] + dp[_lines][_cols - 1] - dp[_lines - 1][_cols - 1] + prim[_lines][_cols];

    while(n--){
        int x1, y1 , x2 , y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }

}
#endif //LEETCODE_TWOPREFIX_H
