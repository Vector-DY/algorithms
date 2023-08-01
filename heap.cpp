#include <iostream>
#include <vector>
using namespace std;
// 递归通过build heapify sort实现  迭代通过heapify2实现  动态的添加方法待维护
class Heap
{
public:
    int size()
    {
        return nums.size();
    }
    int top()
    {
        if (nums.size() == 0)
        {
            return -1;
        }
        return nums[0];
    }
    bool empty()
    {
        return size() == 0 ? true : false;
    }
    Heap() {}
    Heap(vector<int> nums) {
        this->nums = nums;
        buildHeap(this->nums, nums.size());
    }
    ~Heap() {}
    void heapsort()
    {
        int last = size() - 1;
        for (int i = last; i >= 0; i--)
        {
            swap(nums[0], nums[i]);
            heapify2(nums, i, 0);
        }
    }
    void del()
    {
        if (nums.size() == 0)
        {
            return;
        }
        int last = nums.size() - 1;
        swap(nums[0], nums[last]);
        nums.pop_back();
        heapify(nums, nums.size(), 0);
    }
    void print()
    {
        for (auto x : nums)
        {
            cout << x << " ";
        }
        cout << endl;
    }

private:
    vector<int> nums;
    void heapify(vector<int> &nums, int len, int i)
    {
        int l = i * 2 + 1, r = i * 2 + 2;
        int max = i;
        if (l < len && nums[max] < nums[l])
        {
            max = l;
        }
        if (r < len && nums[max] < nums[r])
        {
            max = r;
        }
        if (max != i)
        {
            swap(nums[max], nums[i]);
            heapify(nums, len, max);
        }
    }
    void heapify2(vector<int> &nums, int len, int i) { // 迭代做法
        int j = 2 * i + 1; // 左孩子
        int tmp = nums[i];
        while (j < len) {
            if (j < len - 1 && nums[j] < nums[j + 1]) { //右孩子大
                j++;
            }
            if (tmp < nums[j]) { // parent比孩子小
                nums[i] = nums[j];
                i = j;
                j = 2 * i + 1; // 往下
            } else {
                break;
            }
        }
        nums[i] = tmp;
    }
    void buildHeap(vector<int> &nums, int len)
    {
        int last = len - 1;
        int lastP = (last - 1) / 2;
        for (int i = lastP; i >= 0; i--)
        {
            heapify2(nums, len, i);
        }
    }
};

int main()
{
    vector<int> test2 = {5,3,18,20,1,2, 29, 12};
    Heap heap2(test2);

    heap2.print();
    heap2.heapsort();
    heap2.print();

    return 0;
}