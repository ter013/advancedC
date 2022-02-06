#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
using namespace std::chrono;

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
        std::cout << "measured time: " << duration_cast<T>(time - start).count() << std::endl;
    }

};
int main() {
    double result = 0.;
    {
        //три цикла с остановкой после первого и возобновлением после второго
        Timer<milliseconds> t;
        for (auto i = 0; i < 1000000; i++) {
            result += std::sin(i) + std::cos(i);
        }
        t.stop();
        for (auto i = 0; i < 1000000; i++) {
            result += std::sin(i) + std::cos(i);
        }
        t.renewal();
        for (auto i = 0; i < 1000000; i++) {
            result += std::sin(i) + std::cos(i);
        }

    }
    std::cout << "Resutl is " << result << std::endl;
    return 0;
}
