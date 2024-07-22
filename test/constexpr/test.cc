#include "a.hpp"
#include <iostream>
using namespace std;

constexpr int factorial(int n){
    return n == 0 ? 1 : n * factorial(n-1);
}

void TestForConstexpr(){
    constexpr int a = 10;
    cout << 1 << endl;
    int url[a] = {1,2,3,4,5,6,7,8,9,10};
    for(const auto& e: url){
        cout << e << " ";
    }
    cout << endl;
}

int main(){
    // TestForConstexpr();
    int x = factorial(5);
    cout << x << endl;
    return 0;
}