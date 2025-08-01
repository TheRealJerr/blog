//
// Created by jerry on 2024/8/28.
//
#include "headFile.h"
#ifndef LEETCODE_SORTLIST_H
#define LEETCODE_SORTLIST_H
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int _val,ListNode* _next = nullptr):
        val(_val),next(_next)
    {}
};
ListNode* sortList(ListNode* head) {
    if(head == nullptr || head->next) return head;//当size为0 / 1 可以不用排序了
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* mid_prev = nullptr;
    //双指针找到中间节点
    while(fast && fast->next){
        fast = fast->next->next;
        mid_prev = slow;
        slow = slow->next;;
    }
    mid_prev->next = nullptr;//将两个链表分开
    ListNode* head1 = sortList(head);
    ListNode* head2 = sortList(slow);//将两个链表排序好
    ListNode* newhead = nullptr;
    ListNode* tail = nullptr;//对于一个资深的coder来说,不带头也能轻松应对
    while(head1 || head2)
    {
        ListNode* newtail = nullptr;
        if(head1 == nullptr){
            newtail = head2;
            head2 = head2->next;
        }else if(head2 == nullptr){
            newtail = head1;
            head1 = head1->next;
        }else{
            if(head1->val < head2->val) {
                newtail = head1;
                head1 = head1->next;
            }else {
                newtail = head2;
                head2 = head2->next;
            }
        }
        if(newhead == nullptr)
            newhead = tail = newtail;
        else {
            tail->next = newtail;
            tail = newtail;
        }
    }
    tail->next = nullptr;//封装好
    ListNode* ret = newhead;
    while(ret){
        cout << ret->val << " ";
        ret = ret->next;
    }
    cout << endl;
    return newhead;
}
void test()
{
    ListNode* n1 = new ListNode(-1);
    ListNode* n2 = new ListNode(5);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(0);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    sortList(n1);
}

#endif //LEETCODE_SORTLIST_H
