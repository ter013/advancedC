#include <iostream>
#include <future>
#include <algorithm>
#include <numeric>

template<typename Iterator, class UnaryFunction>
UnaryFunction for_each_block(Iterator first, Iterator last, UnaryFunction f) {
    return std::for_each(first, last, f);
}

template<typename Iterator, class UnaryFunction>
UnaryFunction parallel_for_each(Iterator first, Iterator last, UnaryFunction f) {
    // 1. Проверили длину
    auto length = std::distance(first, last);
    if (length < 32) {
        std::for_each(first, last, f);
    }
    // 2. Длина достаточна, распараллеливаем
    auto num_workers = std::thread::hardware_concurrency();
    // Вычислили длину для одного потока
    auto length_per_thread = length / num_workers;
    // Вектор с потока
    std::vector<std::future<UnaryFunction>> futures;
    // 3. Распределяем данные (концепция полуинтервалов!)
    for(auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = std::next(first, i * length_per_thread);
        auto ending = std::next(first, (i + 1) * length_per_thread);
        // 4. Запускаем исполнителей
        futures.push_back(std::async(std::launch::async, &for_each_block<Iterator, UnaryFunction>, beginning, ending, f));
    }
    futures.push_back(std::async(std::launch::async, &for_each_block<Iterator, UnaryFunction>, std::next(first,
                                    (num_workers - 1) * length_per_thread), last, f));
    for (int i = 0; i < std::size(futures); i++) {
        futures[i].get();
    }
    return f;
}

int main() {

    std::vector<int> test_sequence(100u);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);

    int number = 4;

    parallel_for_each(std::begin(test_sequence), std::end(test_sequence), [&number](auto &x){x += number;});

    std::cout << "Testing programm: ";
    for (auto i: test_sequence) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}