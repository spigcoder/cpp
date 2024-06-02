#include"priority_queue.h"
#include<iostream>
using namespace std;

void test_priority_queue(){
    vector<int> tmp = {1,2,44,5,6,9,54,10};
    spigcoder::priority_queue<int, vector<int>, less<int>> pq;
    for(auto e : tmp) 
    { 
        pq.push(e);
    }
    while(!pq.empty()){
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

int main(){
    test_priority_queue();
    return 0;
}