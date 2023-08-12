#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[parentIndex] < heap[index]) {
                std::swap(heap[parentIndex], heap[index]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;
            int largestIndex = index;

            if (leftChildIndex < size && heap[leftChildIndex] > heap[largestIndex]) {
                largestIndex = leftChildIndex;
            }
            if (rightChildIndex < size && heap[rightChildIndex] > heap[largestIndex]) {
                largestIndex = rightChildIndex;
            }

            if (largestIndex != index) {
                std::swap(heap[index], heap[largestIndex]);
                index = largestIndex;
            } else {
                break;
            }
        }
    }

public:
    bool isEmpty() const {
        return heap.empty();
    }

    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("PriorityQueue is empty.");
        }
        return heap[0];
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("PriorityQueue is empty.");
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
};

int main() {
    PriorityQueue<int> pq;
    pq.push(5);
    pq.push(10);
    pq.push(3);
    pq.push(8);

    while (!pq.isEmpty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }

    return 0;
}
