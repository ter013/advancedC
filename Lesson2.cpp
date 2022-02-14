#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <tuple>

template<typename T, typename ... Types>
auto dynamically_construct(Types... args) {
    return new T(args...);
}

struct date {
    int year, month, day;
};
bool compare_dates(date d1, date d2) {
    return std::make_tuple(d1.year, d1.month, d1.day) < std::make_tuple(d2.year, d2.month, d2.day);
}
//class Fraction{
//public:
//    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
//private:
//    int numerator;
//    unsigned denominator;
//};
#define RANGE(container) container.begin(), container.end() //макрос

bool compare_abs(int lhs, int rhs) {
    return std::abs(lhs) < std::abs(rhs);
}

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

//        std::list<int> numbers = { 1, 3, 2, 42, -255 };
//        std::list<int> other_numbers = { 25, -1, 30 };
//        numbers.splice(std::next(numbers.begin()), other_numbers, other_numbers.begin(), std::prev(other_numbers.end()));
//        numbers.sort(std::greater<>());
//        for (auto item:numbers) {
//            std::cout << item << ' ';
//        }
//        std::cout << std::endl;
//        for (auto item: other_numbers) {
//            std::cout << item << ' ';
//        }
//        std::cout << std::endl;
//
//        numbers.merge(other_numbers);
//        std::cout << "merged: " << std::endl;
//        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));

//int main() {[](){};}
//    std::vector<int> nums {42, 5, -433, 80, 8080};
//    std::sort(RANGE(nums), [](auto lhs, auto rhs) {return std::abs(lhs) < std::abs(rhs);});
//    std::copy(RANGE(nums), std::ostream_iterator<int>(std::cout, " "));

//    std::unordered_map<std::string, unsigned> grades;
//    grades["Denis"] = 3u;
//    std::pair<std::string, unsigned> ilya_grade("Ilya", 9);
//    auto victoria_grade = std::make_pair("Victoria", 8);
//    grades.insert(victoria_grade);
//    grades.insert(ilya_grade);
//
//    grades.insert({"Roman", 7});
//
//    std::cout << grades["Nikita"] << std::endl;

//    for(const auto& student_grade: grades) {
//        std::cout << student_grade.first << ": " << student_grade.second << std::endl;
//    }

//    for(const auto& [student, grade]: grades) {
//        std::cout << student << ": " << grade << std::endl;
//    }

//    std::multimap<int, std::string> groups;
//    groups.emplace(831, "Nikita");
//    groups.insert({831, "Victor"});
//    groups.insert({831, "Alex"});
//    groups.insert({002, "Johnny"});
//    groups.insert({002, "Valery"});
//    groups.insert({001, "Pyotr"});
//
//    for(const auto& [group, student]: groups) {
//        std::cout << std::setw(3) << std::setfill('0') << group << ": "  << student << std::endl;
//    }
//
//    auto [left, right] = groups.equal_range(831);
//    for(auto it = left; it != right; it++) {
//        std::cout << it->second << ' ';
//    }
//    std::cout <<std::endl;
//    std::tuple<int, double, std::string> tuple{1, 2., "a"};
//    date d1{2020, 12, 3};
//    date d2{2020, 11, 5};
//    std::cout << std::boolalpha << compare_dates(d1, d2);
    return 0;
};