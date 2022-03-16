#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>


template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T& result) {
    result = std::accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, int num_workers) { //num_workers - количество потоков.
    // 1. Проверили длину
    auto length = std::distance(first, last);
    if (length < 32) {
        return std::accumulate(first, last, init);
    }
    // 2. Длина достаточна, распараллеливаем
    // Вычислили длину для одного потока
    auto length_per_thread = length / num_workers; //округляем вниз
    // Векторы с потоками и результатами
    std::vector<std::thread> threads;
    std::vector<T> results(num_workers - 1);
    // 3. Распределяем данные (концепция полуинтервалов!)
    for(auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = std::next(first, i * length_per_thread);
        auto ending = std::next(first, (i + 1) * length_per_thread);
        // 4. Запускаем исполнителей
        threads.push_back(std::thread(
                accumulate_block<Iterator, T>,
                beginning, ending, 0, std::ref(results[i])));
    }
    // Остаток данных -- в родительском потоке
    auto main_result = std::accumulate(std::next(first, (num_workers - 1) * length_per_thread),
                                       last, init);
    // std::mem_fun_ref -- для оборачивания join().
    std::for_each(std::begin(threads), std::end(threads), std::mem_fun_ref(&std::thread::join));
    // 5. Собираем результаты
    return std::accumulate(std::begin(results), std::end(results), main_result);
}

int main() {
    std::vector<int> test_sequence(1000000u);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    std::cout << "Time of accumulating from num_workers: " << std::endl;
    for (int i = 1; i < 100; i++) {
        auto start = std::chrono::steady_clock::now();
        auto result =
                parallel_accumulate(std::begin(test_sequence),
                                    std::end(test_sequence), 0, i);
        auto end = std::chrono::steady_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "& " << i << " & " << t << std::endl; // & нужна мне для перевода в Python
    }
    // Комментарии к исследованию масштабируемости и к графикам. Во-первых, я заметил, что с каждым запуском программы
    // значения времён достаточно сильно отличаются для каждого из потоков (похоже, что это уже связано с перераспре-
    // делением процессов в самом компьютере), поэтому я взял серию из 10 измерений, чтобы хоть как-то усреднить.
    // Во-вторых, размер рассматриваемой последовательности сильно влияет. Так, до значения размера последовательности
    // порядка 10^4-10^5 в среднем побеждал однопроцессовый случай. При размере 10^6 уже видно различие. Точечки одного
    // цвета отвечают одному циклу выше. На первом графике изображена общая картина: видно, чтобы бывают сильные выбросы
    // и при большом количестве потоков в среднем время увеличивается. На втором графике приближенная картина. Звёздочки
    // соответсвуют среднему значению времени для данного количества потоков. Видно, что время при одном процессе уже
    // не явлеяется лидером. В среднем, минимальное время достигается при 16 процессах. Таким образом, при малых разме-
    // рах тестовой последовательности, не имеет смысла использовать распараллеливание. Это можно объянить тем, что
    // возникают задержки при распределении процессов и тем, что мы ждём (join()). При больших же размерах тестовой пос-
    // ледовательности, эти задержки становятся меньше времени выполнения обычного accumulate, поэтому там многопроцессо-
    // васть начинает побеждать.
    return  0;
}