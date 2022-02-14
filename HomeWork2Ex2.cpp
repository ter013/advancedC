#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <time.h>

class Phonebook {
private:
    std::map<std::string, unsigned long long> map; // для доступа к данным, отсортированным по фамилии.
    std::unordered_map<std::string, unsigned long long> u_map; // для быстрого поиска по фамилиям.
public:
    Phonebook(): map(), u_map() {}
    void push(std::string const &s, unsigned  long  long t) {
        map.insert({s, t});
        u_map.insert({s,t});
    }
    unsigned long long quick_search(std::string const &s) {
        std::cout << "Subscriber's phone is: ";
        return u_map.find(s)->second;
    }
    void sorted_data() {
        for(const auto& surnames: map) {
            std::cout << surnames.first << " " << surnames.second << std::endl;
        }
    }

    auto random_subscriber() {
        auto t = u_map.size();
        return std::next(std::begin(u_map), rand() % t);
    }
    void delete_sub(std::string const &s) {
        u_map.erase(s);
        map.erase(s);
    }
};

int main() {
    std::srand ( time ( nullptr ) );
    Phonebook a;
    a.push("Ivanov", 89235431212);
    a.push("Sidorov", 89319435174);
    a.push("Stepanova", 89921940324);
    a.push("Grigorev", 89657738814);
    a.push("Dolgov", 89116229978);
    a.push("Andreeva", 89741151555);
    a.push("Nikolaenko", 89533317747);
    a.push("Morgan", 89854451191);
    a.push("Chkaidze", 89779001011);
    a.push("Waserman", 89269961306);

    std::cout << a.quick_search("Morgan") << std::endl << std::endl; //демонстрация быстрого поиска по фамилии
    std::cout << "Sorted data: " << std::endl;
    a.sorted_data(); // отсортированные данные справочника.
    std::cout << std::endl;
    auto r = a.random_subscriber();
    std::cout << "Random subscriber: " << std::endl;
    std::cout << r->first << " " << r->second << std::endl << std::endl;
    std::cout << "Deleting subscriber from phonebook: " << std::endl;
    a.delete_sub("Ivanov");
    a.sorted_data();
}