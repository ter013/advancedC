#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <cstdlib>
#include <algorithm>

using namespace std::chrono;
#define RANGE(container) container.begin(), container.end() //макрос

template<typename T>
class Timer {
private:
    steady_clock::time_point  start;
    steady_clock::time_point  current_start;
    steady_clock::time_point  time;
public:
    Timer(): start(steady_clock::now()), time(steady_clock::now()), current_start(steady_clock::now()) {}
    void stop() {
        auto t = steady_clock::now() - current_start;
        time += t;
        current_start = start;
    };
    void renewal() {
        current_start = steady_clock::now();
    }
    ~Timer() {
        if (current_start > start) {
            stop();
        }
        std::cout << duration_cast<T>(time - start).count() << std::endl;
    }

};

int main() {
    const int n = 10000;

    std::array<int, n> array;
    std::vector<int> vector;
    std::deque<int> deque;
    std::list<int> list;
    std::forward_list<int> f_list;

    for (int i = 0; i < 10000; i++) {
        int x = rand() - rand();
        array[i] = x;
        vector.push_back(x);
        deque.push_back(x);
        list.push_back(x);
        f_list.push_front(x);
    }

    std::cout << "Sorting time of array: ";
    {
        Timer<microseconds> t;
        std::sort(RANGE(array));
    }

    std::cout << "Sorting time of vector: ";
    {
        Timer<microseconds> t;
        std::sort(RANGE(vector));
    }

    std::cout << "Sorting time of deque: ";
    {
        Timer<microseconds> t;
        std::sort(RANGE(deque));
    }

    std::cout << "Sorting time of list: ";
    {
        Timer<microseconds> t;
        list.sort();
    }

    std::cout << "Sorting time of forward_list: ";
    {
        Timer<microseconds> t;
        f_list.sort();
    }

    std::cout << "We can see, that array has the least time of sorting.";
}