#include "a.hpp"
#include <memory>
#include <iostream>
using namespace std;

void TestSharedPtr(){
    shared_ptr<int> p1(nullptr);
    cout << p1.unique() << endl;
}

int main(){
    TestSharedPtr();
    return 0;
}