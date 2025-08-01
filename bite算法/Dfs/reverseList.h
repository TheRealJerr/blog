// 反转链表
// 2025/2/7
#include "../headFile.h"
#include "../include/ListNode.h"
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return Dfs(head).first;
    }
    pair<ListNode*,ListNode*> Dfs(ListNode* head) // 返回的是头和尾
    {
        if(head == nullptr) return { nullptr, nullptr};
        else if(head->next == nullptr) return { head, head };

        auto newlist = Dfs(head->next); 

        newlist.second->next = head;
        head->next = nullptr; // 这里为了避免出现悬空指针
        return { newlist.first, head};
    }
};