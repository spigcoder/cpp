#include"priority_queue.h"
#include<iostream>
using namespace std;

void test_priority_queue(){
    
    vector<int> tmp = {1,2,44,5,6,9,54,10};
    vector<int> tmp1 = {1,2,3,4,5,6,7,8,9,10};
    vector<int> tmp2 = tmp1;
    reverse(tmp2.begin(), tmp2.end());
    for(auto e : tmp) 
    { 
        pq.push(e);
    }
    for(auto e : tmp) 
    { 
        pq.push(e);
    }
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