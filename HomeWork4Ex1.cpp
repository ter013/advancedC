#include <iostream>
#include <iterator>
#include <fstream>
#include "json.hpp"
#include <filesystem>

using json = nlohmann::json;

struct human{
    std::string name;
    int age = 0;
    float weight = 0;
    float height = 0;
};

std::istream& operator>> (std::istream &t, human & p) {
    std::cout << "Enter the person's name, age, weight, height" << std::endl;
    std::string a;
    std::cin >> a;
    p.name = a;
    int b;
    std::cin >> b;
    p.age = b;
    float c;
    std::cin >> c;
    p.weight = c;
    float d;
    std::cin >> d;
    p.height = d;
    return t;
}

int main() {
    human M1, M2, M3;
    std::cin >> M1 >> M2 >> M3;
    json object1;
    object1["Name"] = M1.name;
    object1["Age"] = M1.age;
    object1["Weight"] = M1.weight;
    object1["Height"] = M1.height;

    json object2;
    object2["Name"] = M2.name;
    object2["Age"] = M2.age;
    object2["Weight"] = M2.weight;
    object2["Height"] = M2.height;

    json object3;
    object3["Name"] = M3.name;
    object3["Age"] = M3.age;
    object3["Weight"] = M3.weight;
    object3["Height"] = M3.height;
    std::cout << object1.dump(2) << std::endl;
    std::cout << object2.dump(2) << std::endl;
    std::cout << object3.dump(2) << std::endl;

    std::filesystem::path parent_directory("..");
    std::filesystem::create_directory("Catalog");

    auto path_to_main = parent_directory / "HomeWork4Ex1.cpp";
    auto new_path = parent_directory / "cmake-build-debug" / "Catalog";

    auto text1 = new_path / "text1.txt";
    std::ofstream recorder1(text1, std::ios::out);
    recorder1 << object1.dump(4);
    recorder1.close();

    auto text2 = new_path / "text2.txt";
    std::ofstream recorder2(text2, std::ios::out);
    recorder2 << object1.dump(4);
    recorder2.close();

    auto text3 = new_path / "text3.txt";
    std::ofstream recorder3(text3, std::ios::out);
    recorder3 << object1.dump(4);
    recorder3.close();

    return 0;
}