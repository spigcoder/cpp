#include<iostream>
#include"stack.h"
using namespace std;

void TestStack(){
    spigcoder::stack<int> st;
    st.push(1); 
    st.push(2); 
    st.push(3); 
    st.push(4); 
    while(!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }
}

int main(){
    TestStack();
    return 0;
}