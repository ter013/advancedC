#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <iterator>
#include <algorithm>

class Fraction{
public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
private:
    int numerator;
    unsigned denominator;
};

int main() {
//    std::vector<int> numbers;
//    for(auto i = 0; i < 30; i++) {
//        numbers.push_back(i);
//        std::cout <<"size is " << numbers.size() << ", capacity is " << numbers.capacity() << std::endl;
//    }
//

//    std::deque<Fraction> deque;
//    deque.emplace_front(1, 25u);
//    std::cout << deque.size();

        std::list<int> numbers = { 1, 3, 2, 42, -255 };
        std::list<int> other_numbers = { 25, -1, 30 };
        numbers.splice(std::next(numbers.begin()), other_numbers, other_numbers.begin(), std::prev(other_numbers.end()));
        numbers.sort(std::greater<>());
        for (auto item:numbers) {
            std::cout << item << ' ';
        }
        std::cout << std::endl;
        for (auto item: other_numbers) {
            std::cout << item << ' ';
        }
        std::cout << std::endl;

        numbers.merge(other_numbers);
        std::cout << "merged: " << std::endl;
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
};