//
// Created by jerry on 2024/10/17.
//
#include "headFile.h"
#ifndef LEETCODE_KMP_H
#define LEETCODE_KMP_H
vector<int> getNextArray(const string& base){
    vector<int> nextArray(base.size(),0);
    int array_cur = 0;
    for(int cur = 1;cur < base.size();cur++){
        if(base[cur] == base[array_cur]) nextArray[cur] = ++array_cur;
        else{
            array_cur = 0;
            if(base[cur] == base[array_cur]) nextArray[cur] = ++array_cur;
            else nextArray[cur] = 0;
        }
    }
    return nextArray;
}
int kmpMethod(const string& base,const string& target){
    //这里我们要去target中找到base字符串并且返回下标,如果没有返回 -1
    vector<int> nextArray = getNextArray(base);
    int target_cur = 0;
    for(int base_cur = 0;base_cur < base.size();base_cur++)
    {
        //匹配继续往后面走
        if(base[base_cur] == target[target_cur]) {
            target_cur++;
            if(target_cur == target.size()) return base_cur - target.size() + 1;//
            //
        }else{//如果说不匹配,用到我们这里的nextArray
            if(target_cur > 0 && nextArray[target_cur - 1]){
                base_cur--;//base_cur回滚
                target_cur--;
                target_cur = target_cur == -1 ? target_cur = 0 : nextArray[target_cur] + 1;
            }
        }
    }
    return -1;
}
#endif //LEETCODE_KMP_H
