//
// Created by jerry on 2024/10/6.
//
#include "headFile.h"
#ifndef LEETCODE_CONVERT_H
#define LEETCODE_CONVERT_H
string convert(string s,int numRows)
{
    vector<vector<char>> vvch(numRows);
    int pos = 1;//这个表示的是第几个Z
    int n = s.size();
    int tmp = (numRows - 1) * 2;
    int sizeN = (s.size() - 1) / tmp;
    if((n - 1) % tmp) sizeN++;
    for(auto& e : vvch)
        e.resize(1 + (numRows - 1) * sizeN,' ');
    vvch[0][0] = s[0];
    int strpos = 1;
    for(;pos <= sizeN;pos++){
        for(int i = 1;i < numRows;i++){
            if(strpos == s.size()) break;
            vvch[i][(pos-1)*(numRows-1)] = s[strpos++];
        }
        for(int j = 1;j < numRows;j++){
            if(strpos == s.size()) break;
            vvch[numRows - 1 - j][(pos-1)*(numRows-1) + j] = s[strpos++];
        }
    }
    string ret;
    ret.resize(s.size());
    int cur = 0;
    for(auto& e : vvch)
        for(char ch : e)
            if(ch != ' ') ret[cur++] = ch;
    return ret;
}
void test()
{
    string task = "PAYPALISHIRING";
    cout << convert(task,3);
}
#endif //LEETCODE_CONVERT_H
