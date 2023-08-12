#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 10;

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        lock.unlock();
        cv.notify_all();
    }
}

void consumer() {
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;

        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
