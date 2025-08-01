//
// Created by jerry on 2024/8/31.
//
#include "headFile.h"
#ifndef LEETCODE_REVERSEKGROUP_H
#define LEETCODE_REVERSEKGROUP_H
struct ListNode{
    ListNode* next;
    int val;
    ListNode(int _val,ListNode* _next = nullptr):val(_val),next(_next)
    {}
};
pair<ListNode*,ListNode*> reverse(ListNode* head)//这里我们进行翻转的时候默认尾部以nullptr进行结尾
{
    if(head == nullptr || head->next == nullptr) return make_pair(head,head);
    ListNode* firs = head, *secon = head->next, *thir = head->next->next;
    head->next = nullptr;
    while(thir)
    {
        secon->next = firs;
        firs = secon;
        secon = thir;
        thir = thir->next;
    }
    secon->next = firs;
    return make_pair(secon,head);
}
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head == nullptr || head->next == nullptr || k == 1) return head;
    ListNode* begin = head , *end = head;
    pair<ListNode*,ListNode*> prevNodeInfor(nullptr,nullptr);
    vector<ListNode*> skLN;
    while(begin && end)
    {
        int sizeofK = k - 1;
        while(end && sizeofK > 0)
        {
            end = end->next;
            sizeofK--;
        }
        skLN.push_back(end);
        if(end == nullptr) {
            prevNodeInfor.second->next = begin;
            break;
        }
        ListNode* seq = end->next;//后继节点
        end->next = nullptr;//封装好
        pair<ListNode*,ListNode*> curNodeInfor = reverse(begin);
        if(prevNodeInfor.second) prevNodeInfor.second->next = curNodeInfor.first;
        prevNodeInfor = curNodeInfor;
        begin = end = seq;
    }
    return skLN.front();
}
void test()
{
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(5);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    auto ret = reverseKGroup(n1,2);
    ListNode* head = ret;
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
}

#endif //LEETCODE_REVERSEKGROUP_H
