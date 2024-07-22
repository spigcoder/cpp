#include <iostream>
using namespace std;

#include <iostream>
using namespace std;
//重载被调用函数，查看完美转发的效果
void otherdef(int & t) {
    cout << "lvalue\n";
}
void otherdef(int && t) {
    cout << "rvalue\n";
}
//实现完美转发的函数模板
template <typename T>
void function(T&& t) {
    otherdef(forward<T>(t));
}
int main()
{
    function(5);
    int  x = 1;
    function(x);
    return 0;
}

                        

                        

                        