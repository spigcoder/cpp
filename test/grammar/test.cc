#include "a.hpp"
#include <memory>
#include <utility>
#include <iostream>
using namespace std;

constexpr int func(){
    return 10;
}

int main() {
    std::string str = "Hello";
    const char* new_str = "World";
    std::string old_str = exchange(str, "World"); // str 变成 "World"，old_str 是 "Hello"

    std::cout << "str: " << str << "\n";       // 输出 str: World
    str = "nihoa";
    std::cout << "str: " << str << "\n";       // 输出 str: World
    std::cout << "old_str: " << old_str << "\n"; // 输出 old_str: Hello
    cout << new_str << endl;
    return 0;
}