cmake_minimum_required(VERSION 3.20)
project(advancedC__)



set(CMAKE_CXX_STANDARD 20)

#set(Boost_INCLUDE_DIR C:/MinGW/include/)
#set(Boost_LIBRARY_DIR C:/MinGW/lib/)
#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(advancedC__ main.cpp)
add_executable(second Lesson2.cpp)
add_executable(second1 HomeWork2Ex1.cpp)
add_executable(second2 HomeWork2Ex2.cpp HomeWork2Ex2.cpp)
add_executable(third Lesson3.cpp)
add_executable(third1 HomeWork3.cpp)
add_executable(fourth Lesson4.cpp)
add_executable(fourth1 HomeWork4Ex1.cpp json.hpp)
add_executable(fourth2 HomeWork4Ex2.cpp)
add_executable(fifth Lesson5.cpp)
add_executable(fifth1 HomeWork5Ex1.cpp)
add_executable(fifth2 HomeWork5Ex2.cpp)
add_executable(six Lesson6.cpp)
add_executable(seven Lesson7.cpp)
add_executable(seven1  Lesson71.cpp)
add_executable(eight Lesson8.cpp)
add_executable(nine HomeWork6Ex1.cpp)
add_executable(ten1 HomeWork6Ex2.cpp)

target_link_libraries(seven ws2_32)
target_link_libraries(seven1 ws2_32)
target_link_libraries(eight ${PYTHON_LIBRARIES})