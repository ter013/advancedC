#include <iostream>
#include <chrono>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>

template<typename  T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& container) {
    out << '[';
    std::copy(std::begin(container), std::prev(std::end(container)), std::ostream_iterator<T>(out, ", "));
    out << *(std::prev(std::end(container))) << ']';
    return out;
}
#define RANGE(container) std::begin(container), std::end(container)
bool Prime(unsigned long a) {
    if (a == 2 or a == 3) {
        return true;
    }
    else if (!(a % 2) or !(a % 3) or a == 1) {
        return false;
    }

    for (int divider = 5; divider <= sqrt(a); divider += 2) {
    if (!(a % divider)) {
        return false;
    }
    }
    return true;
}

int main() {
    std::cout << "1. Create first sequence P1:";
    std::vector<int> P1(10);
    std::iota(RANGE(P1), 1);
    std::cout << P1 << std::endl;

    std::cout << "Enter additional numbers:" << std::endl;
    int x;
    while (std::cin >> x) {
        P1.push_back(x);
    }
    std::cout << "2. Adding numbers to the end of P1 from cin: ";
    std::cout << P1 << std::endl;

    auto seed1 = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 g(seed1);
    std::shuffle(RANGE(P1), g);
    std::cout << "3. Shuffle the sequence P1 randomly: ";
    std::cout << P1 << std::endl;

    std::sort(RANGE(P1)); //проблема, что здесь используется сортировка
    auto dublicates = std::unique(RANGE(P1));
    P1.erase(dublicates, P1.end());
    std::cout << "4. Removing duplicates from P1: ";
    std::cout << P1 << std::endl;

//    int size = P1.size(); // через циклы можно удалить дубликаты с сохранением порядка элементов, но это будет явно дольше
//    for (int i = 0; i < size; i++) {
//        for (int j = i + 1; j < size; j++) {
//            if (P1[i] == P1[j]) {
//                for (int k = j; k < size - 1; k++) {
//                    P1[k] = P1[k + 1];
//                }
//                size--;
//                P1.pop_back();
//            }
//        }
//    }
//    std::cout << "4. Removing duplicates from P1: ";
//    std::cout << P1 << std::endl;

    int odd_numbers;
    for(auto number: P1) {
        if (number % 2 != 0) {odd_numbers++;}
    }
    std::cout << "5. Number of odd numbers in P1: ";
    std::cout << odd_numbers <<std::endl;

//    int min_P1 = P1[0], max_P1 = P1[0]; // это для несортированного массива
//    for (int i = 1; i < P1.size(); i++) {
//        if (P1[i] > max_P1) {max_P1 = P1[i];}
//        if (P1[i] < min_P1) {min_P1 = P1[i];}
//    }
    int min_P1 = *P1.begin(); int max_P1 = *(P1.end() - 1);
    std::cout << "6. Minimum number in P1: " << min_P1 << ", " << "Maximum number in P1: " << max_P1 << std::endl;


    std::cout << "7. Prime numbers in P1: ";
    for (auto number: P1) {
        if (number >= 0) {
            if (Prime(number)) {
                std::cout << number << "; ";
            }
        }
    }
    std::cout << std::endl;


    std::transform(RANGE(P1), P1.begin(), [](auto  x){return x * x;});
    std::cout << "8. Replacing numbers in P1 with squares: ";
    std::cout << P1 << std::endl;

    auto seed2 = std::chrono::steady_clock::now().time_since_epoch().count();
    auto generator2 = std::mt19937(seed2); //mersenne twister
    auto distribution2 = std::uniform_int_distribution(-1000, 1000); //взял не слишком большой диапозон для красоты восприятия
    std::vector<int> P2;
    std::generate_n(std::back_inserter(P2), P1.size()  , [&generator2, &distribution2](){return distribution2(generator2);});
    std::cout << "9. Create a P2 sequence from random numbers: "  << P2 << std::endl;

    std::cout << "10. Sum of numbers P2: " << std::accumulate(std::begin(P2), std::end(P2), 0) << std::endl;

    std::transform(P2.begin(), std::next(std::begin(P2), std::size(P2) / 3), P2.begin(), [](auto x){return 1;});
    std::cout << "11. Replacing the first few numbers P2 with the number 1: " << P2 << std::endl;

    std::vector<int> P3;// хотел как-то через std::transform, не вышло
    auto a = P1.begin();
    auto b = P2.begin();
    for (int i = 0; i < std::size(P1); i++) {
        P3.push_back(*a - *b);
        a++;
        b++;
    }
    std::cout << "12. Sequence P3 as the difference between P1 and P2: " << P3 << std::endl;
    std::transform(RANGE(P3), P3.begin(), [](auto x){if (x < 0) {return  0;} else{return  x;}});
    std::cout << "13. Replacing each negative element in the P3 with zero: " << P3 << std::endl;

    for(auto i = 0; i != std::size(P3);) {
        if (P3[i] == 0) {
            P3.erase(std::next(P3.begin(), i));
        }
        else {i++;}
    }
    std::cout << "14. Removing all zero elements from the P3: " << P3 << std::endl;
    std::vector<int> d(std::size(P3));
    std::reverse_copy(RANGE(P3), d.begin());
    P3 = d;
    std::cout << "15. Changing the order of the elements in the P3 to reverse: " << d << std::endl;

    std::sort(RANGE(P3));
    std::cout << "16. Quick determination of the top 3 largest elements in the P3: " << *(P3.end() - 1) << ", " << *(P3.end() - 2) << ", " << *(P3.end() - 3) << std::endl;

    std::sort(RANGE(P1), [](auto lhs, auto rhs){return lhs < rhs;});
    std::sort(RANGE(P2), [](auto lhs, auto rhs){return lhs < rhs;});
    std::cout << "17. Sorted P1 and P2 in ascending order: " << std::endl;
    std::cout << "P1: " << P1 << std::endl;
    std::cout << "P2: " << P2 << std::endl;

    std::vector<int> P4;
    std::merge(P1.begin(),  P1.end(), P2.begin(), P2.end(), std::back_inserter(P4), [](auto x, auto y){return  x < y;});
    std::cout << "18. Creation of the P4 sequence as a merger of P1 and P2: " << P4 << std::endl;

    auto first = P4.begin();// итератор на место первой единицей
    auto second = P4.begin();// итератор на место после последней единицы
    while(*first != 1) {//я использую тот факт, что в P2 всегда есть единицы, а значит и в P4
        first++;
    }
    second = first;
    while(*second == 1) {
        second++;
    }
    std::cout << "19. Determination of the range for the ordered insertion of the number 1 in P4 (*first, *(first - 1), *second(-1), *second): ";
    std::cout << *first << " " << *(first - 1) << " " << *(second - 1) << " " << *second << std::endl;
    std::cout << "20. All sequences:" << std::endl;
    std::cout << "P1: " << P1 << std::endl;
    std::cout << "P2: " << P2 << std::endl;
    std::cout << "P3: " << P3 << std::endl;
    std::cout << "P4: " << P4 << std::endl;
};