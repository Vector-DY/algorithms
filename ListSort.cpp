#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class solution {
public:
    ListNode* quickSortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        auto left = new ListNode(-1), mid = new ListNode(-1), right = new ListNode(-1);
        auto ltail = left, mtail = mid, rtail = right;
        int val = head->val;
        for (auto p = head; p != nullptr; p = p->next) {
            if (p->val < val) {
                ltail = ltail->next = p;
            } else if (p->val == val) {
                mtail = mtail->next = p;
            } else {
                rtail = rtail->next = p;
            }
        }
        ltail->next = mtail->next = rtail->next = nullptr;
        left->next = quickSortList(left->next);
        right->next = quickSortList(right->next);

        get_tail(left)->next = mid->next;
        get_tail(mid)->next = right->next;

        return left->next;

    }

    ListNode* get_tail(ListNode* head) {
        while (head->next) {
            head = head->next;
        }
        return head;
    }
};

int main()
{
    solution a;
    ListNode *head = new ListNode(2);
    head->next = new ListNode(3);
    head->next->next = new ListNode(1);
    head = a.quickSortList(head);

    for (auto p = head; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }

    return 0;

}