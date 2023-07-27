#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 计算两个链表之差的绝对值
     * @param pListHead1 ListNode类 第一个整数链表
     * @param pListHead2 ListNode类 第二个整数链表
     * @return ListNode类
     */
    string strSub(string a, string b) {
        if (a == b) {
            return "0";
        }
        if (a.size() < b.size()) {
            swap(a, b);
        }
        if (a.size() == b.size() && a < b) {
            swap(a, b);
        }
        int i = a.size() - 1, j = b.size() - 1;
        int flag = 0;
        string ans;
        while (i >= 0 && j >= 0) {
            int t = 0;
            if (a[i] >= b[j]) {
                t = a[i] - b[j];
                t = t - flag;
                ans += to_string(t);
                flag = 0;
            } else {
                t = a[i] - b[j] + 10;
                t = t - flag;
                ans += to_string(t);
                flag = 1;
            }
            i--;
            j--;
        }
        while (i >= 0) {
            if (flag == 0) {
                ans += a[i];
            } else {
                int t = a[i] - '0' - flag;
                ans += to_string(t);
                flag = 0;
            }
            i--;
        }
        reverse(ans.begin(), ans.end());
        i = 0;
        while (ans[i] == '0') {
            i++;
        }
        ans = ans.substr(i);
        return ans;
    }

    ListNode* ListNumSubAbs(ListNode* pListHead1, ListNode* pListHead2) {
        // write code here
        if (pListHead1 == nullptr && pListHead2 == nullptr) {
            return nullptr;
        }
        string a, b;
        ListNode* head1 = pListHead1, *head2 = pListHead2;
        while (head1 != nullptr) {
            a += to_string(head1->val);
            head1 = head1->next;
        }
        while (head2 != nullptr) {
            b += to_string(head2->val);
            head2 = head2->next;
        }
        cout << a << endl << b << endl;
        string abx = strSub(a, b);
        cout << abx << endl;
        auto* dummy = new ListNode(-1);
        auto* nxt = new ListNode(0);
        dummy->next = nxt;
        int i = 0;
        while (i < abx.size()) {
            nxt->val = abx[i] - '0';
            if (i != abx.size() - 1) {
                nxt->next = new ListNode(0);
                nxt = nxt->next;
            }
            i++;
        
        }

        return dummy->next;
    }
};

int main()
{
    Solution c;
    auto *a = new ListNode(1);
    a->next = new ListNode(2);
    a->next->next = new ListNode(3);
    auto *b = new ListNode(4);
    b->next = new ListNode(2);
    b->next->next = new ListNode(3);
    auto ans = c.ListNumSubAbs(a, b);
    while (ans != nullptr) {
        cout << ans->val << " ";
        ans = ans->next;
    }
    return 0;
} 