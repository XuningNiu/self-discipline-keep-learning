方法一: recursive的递归做法：
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode *end = nullptr;
    ListNode *reverseN(ListNode *head, int n){
        if (n == 1){
            end = head->next;
            return head;
        }
        ListNode *newHead = reverseN(head->next, n-1);
        head->next->next = head;
        head->next = end;
        return newHead;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == 1){
            return reverseN(head, right);
        }
        head->next = reverseBetween(head->next, left-1, right-1);
        return head;
    }
};

//原始出处

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // base case
        if (m == 1) {
            return reverseN(head, n);
        }
        // 前进到反转的起点触发 base case
        head->next = reverseBetween(head->next, m - 1, n - 1);
        return head;
    }

private:
    ListNode* successor = nullptr; // 后驱节点
    // 反转以 head 为起点的 n 个节点，返回新的头结点
    ListNode* reverseN(ListNode* head, int n) {
        if (n == 1) {
            // 记录第 n + 1 个节点
            successor = head->next;
            return head;
        }
        // 以 head->next 为起点，需要反转前 n - 1 个节点
        ListNode* last = reverseN(head->next, n - 1);

        head->next->next = head;
        // 让反转之后的 head 节点和后面的节点连起来
        head->next = successor;
        return last;

    }
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=reverse-linked-list-ii

//方法二： 迭代做法，找到开始跳转的位置，for循环reverse
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy;
        dummy.next = head;
        ListNode *pre = &dummy;

        for (int i = 1; i < left; i++){ //注意这里是 <
            pre = pre->next;
        }
        ListNode *cur = pre->next;
        ListNode *record_pre = pre;   //注意这里要记录
        ListNode *record_cur = pre->next; //注意这里要记录

        for (int i = left; i <= right; i++){  //注意这里是 <=
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        record_cur->next = cur;
        record_pre->next = pre;

        return dummy.next;
    }
};