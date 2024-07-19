#include <vector>
#include <iostream>
using namespace std;

int main(){
    int num1 = 1, num2 = 2, num3 = 3;
    //对于被mutable修饰的lambda表达式，前面的()不可以省略
    vector<int> x;
    x.push_back(1);
    // cout << x.end() << endl;
    return 0;
}