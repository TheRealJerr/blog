// 便于测试后面的代码
struct ListNode 
{
    int val;
    struct ListNode* next;
    ListNode(int val = 0,ListNode* next = nullptr)
        :val(val),next(next)
    {}
};
