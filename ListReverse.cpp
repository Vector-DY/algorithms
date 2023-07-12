#include <iostream>

using namespace std;
template <class T>
struct ListNode
{
    T val;
    struct ListNode<T> *next;
    ListNode(int d) : val(d), next(nullptr) {}
    ListNode(int d, ListNode<T> *n) : val(d), next(n) {}
};

ListNode<int> *reverse(ListNode<int> *head)
{
    if (head == nullptr) {
        return head;
    }
    ListNode<int> *pre = nullptr;
    ListNode<int> *cur = head;
    while (cur) {
        ListNode<int> *nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

int main()
{
    ListNode<int> *head = new ListNode<int>(1);
    head->next = new ListNode<int>(2);
    head->next->next = new ListNode<int>(3);
    cout << "--------previous---------" << endl;
    for (auto it = head; it != nullptr; it = it->next) {
        cout << it->val << " ";
    }
    cout << endl;
    head = reverse(head);
    cout << "--------after reverse---------" << endl;
    for (auto it = head; it != nullptr; it = it->next) {
        cout << it->val << " ";
    }
    cout << endl;
    return 0;
}