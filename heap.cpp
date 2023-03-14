#include <iostream>
#include <vector>
using namespace std;

class Heap
{
public:
    int size()
    {
        return nums.size();
    }
    vector<int> nums;
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
    ~Heap() {}
    void heapsort()
    {
        int last = size() - 1;
        for (int i = last; i >= 0; i--)
        {
            swap(nums[0], nums[i]);
            heapify(nums, i, 0);
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
    void add(int num)
    {
        nums.push_back(num);
        int son = nums.size() - 1;
        int parent = (son - 1) / 2;
        while (parent >= 0 && nums[son] > nums[parent])
        {
            swap(nums[son], nums[parent]);
            son = parent;
            parent = (son - 1) / 2;
        }
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
    void buildHeap(vector<int> &nums, int len)
    {
        int last = len - 1;
        int lastP = (last - 1) / 2;
        for (int i = lastP; i >= 0; i--)
        {
            heapify(nums, len, i);
        }
    }
};

int main()
{
    Heap heap;
    cout << heap.empty() << endl;
    cout << heap.size() << endl;
    cout << heap.top() << endl;

    heap.add(5);
    heap.add(4);
    heap.add(18);
    heap.add(20);
    heap.add(1);
    heap.heapsort();
    heap.print();
    cout << heap.size() << endl;
    cout << heap.top() << endl;

    return 0;
}