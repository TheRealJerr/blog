// create by hrj
// Current time: 2025-02-13 20:44:59.256
#include "/home/hrj/leetcode/headFile.h"

class Solution
{
private:
    vector<string> ret;
    std::string path;
    bool isAlphabet(char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    std::string getAlphabetIllustrate(char ch)
    {
        std::string tmp;
        if(ch >= 'a' && ch <= 'z')
        {
            tmp.push_back(ch);
            tmp.push_back(ch - 32);
        } 
        else 
        {
            tmp.push_back(ch);
            tmp.push_back(ch + 32);
        }
        return tmp;
    }
public:

    void dfs(const std::string& s,int pos)
    {
        if(path.size() == s.size())
        {
            ret.push_back(path);
            return;
        }
        std::string letter;
        if(isAlphabet(s[pos]))
            // 字母
            letter = getAlphabetIllustrate(s[pos]);
        else letter = s[pos];
        for(auto choice: letter)
        {
            path.push_back(choice);
            dfs(s,pos + 1);
            // 回溯
            path.pop_back();
        }
        return;
    }

    vector<string> letterCasePermutation(string s)
    {
        dfs(s,0);
        return ret;
    }
};