#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <queue>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void push(T elem) {
        std::lock_guard guard(mutex);
        queue.push(elem);
    }
    T front() {
        std::lock_guard guard(mutex);
        return queue.front();
    }
    void pop() {
        std::lock_guard guard(mutex);
        queue.pop();
    }
    T back() {
        std::lock_guard guard(mutex);
        return queue.back();
    }
    bool empty() {
        std::lock_guard guard(mutex);
        return queue.empty();
    }
    auto emplace() {
        std::lock_guard guard(mutex);
        return queue.template emplace();
    }
    
    auto size() {
        std::lock_guard guard(mutex);
        return queue.size();

    }
private:
    std::queue<T> queue;
    std::mutex mutex;
};

void push_n_times(ThreadSafeQueue<int>& queue, int n) {
    for (int i = 0; i < n; i++) {
        queue.push(i);
    }
}
int main() {
    int n = 100;
    ThreadSafeQueue<int> queue;
    for (auto i = 0; i < n; i++) {
        queue.push(1);
    }
    std::thread thread(push_n_times, std::ref(queue), n);
    thread.join();

    for (int i = 0; i < n; i++) {
        queue.pop();
    }
    std::cout << "Stack size is " << queue.size() << std::endl;
    //вроде на выводе всё окей
    return 0;
}