#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <cmath>
#include <vector>
#include <numeric>

//возьмём алгоритм, включающий потоки, разобранный на занятии
template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T& result) {
    result += std::accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, T& answer) {

    std::mutex mutex; //мьютекс для контроля добавления значения к answer

    // 1. Проверили длину
    auto length = std::distance(first, last);
    if (length < 32) {
        std::lock_guard guard0(mutex);
        answer += std::accumulate(first, last, init);
    }

    // 2. Длина достаточна, распараллеливаем
    auto num_workers = std::thread::hardware_concurrency();
    // Вычислили длину для одного потока
    auto length_per_thread = length / num_workers; //округляем вниз


    // 3. Распределяем данные (концепция полуинтервалов!)
    for (auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = std::next(first, i * length_per_thread);
        auto ending = std::next(first, (i + 1) * length_per_thread);

        // 4. Запускаем исполнителей
        {
            std::lock_guard guard(mutex);
            std::thread thread(std::thread(
                    accumulate_block<Iterator, T>,
                    beginning, ending, 0, std::ref(answer)));
            thread.join(); //ждём
        }
    }

    // Остаток данных -- в родительском потоке
    {
        std::lock_guard Guard(mutex);
        answer += std::accumulate(std::next(first, (num_workers - 1) * length_per_thread),
                                           last, init);
    }

    // 5. ОТдаём результат
    return answer;
}

int main() {
    int answer = 0;
    std::vector<int> test_sequence(100u);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    std::cout << "Result is " << parallel_accumulate(std::begin(test_sequence),
            std::end(test_sequence), 0, answer);
    return 0;
}
