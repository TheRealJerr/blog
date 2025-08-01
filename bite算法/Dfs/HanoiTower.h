// 汉诺塔problem
// create by hrj by 2025/2/
#include "../headFile.h"
class Solution {
public:
    void hanotaHelper(vector<int>& A,vector<int>& B,vector<int>& C,int k)
    {
        // k表示转移的个数
        if(k == 0) return;
        hanotaHelper(A,C,B,k - 1);
        C.push_back(A.back());
        A.pop_back();
        hanotaHelper(B,A,C,k - 1);
    }
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        // this function is move A to C
        hanotaHelper(A,B,C,A.size());
    }
};