#include <tuple>
#include <string>
#include <iostream>
using namespace std;

void TestTuple(){
    tuple<int, string, double> i_str(10, "hello tuple", 6.66);
    cout << tuple_size<decltype(i_str)>::value << endl;
    cout << get<0>(i_str) << " " << get<1>(i_str) << " " << get<2>(i_str) << endl;
    int x = 0;
    string str = "";
    double d;
    tie(x, str, d) = i_str;
    cout << x << str << d;
}

int main(){
    TestTuple();
    return 0;
}