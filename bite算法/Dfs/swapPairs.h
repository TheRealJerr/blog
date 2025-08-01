#include "../headFile.h"
#include "../include/ListNode.h"

// 2025/2/7
// 两两交换链表中的节点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
       // 通过递归来实现
       if(head == nullptr || head->next == nullptr) return head;

       // 截取两个节点
       ListNode* prev = head, *cur = head->next;
       // 递归
       ListNode* next = swapPairs(cur->next);
       // 连接操作
       cur->next = prev;
       prev->next = next;
       // 返回新的头
       return cur;
    }
};