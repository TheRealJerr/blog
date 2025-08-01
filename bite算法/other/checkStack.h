//
// Created by jerry on 2024/10/9.
//
#include "headFile.h"
#ifndef LEETCODE_CHECKSTACK_H
#define LEETCODE_CHECKSTACK_H
bool checkStack(vector<int>& isk,vector<int>& osk)
{
    stack<int> checksk;
    int outpos = 0;
    for(int i : isk){
        checksk.push(i);
        while(!checksk.empty() && osk[outpos] == checksk.top()){
            checksk.pop();
            outpos++;
        }
    }
    return checksk.empty();
}
void testcheckStack()
{
    int q = 0;
    cin >> q;
    for(int i = 0;i < q;i++){
        int n = 0;
        cin >> n;
        vector<int> in(n), out(n);
        for(int j = 0;j < n;j++)
            cin >> in[j];
        for(int j = 0;j < n;j++)
            cin >> out[j];
        bool ret = checkStack(in,out);
        if(ret) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}
#endif //LEETCODE_CHECKSTACK_H
