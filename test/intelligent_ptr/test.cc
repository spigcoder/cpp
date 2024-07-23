#include <memory>
#include <iostream>
using namespace std;

struct Node{
    Node(int val){
        _val = val;
        left = nullptr;
        right = nullptr;
    }
    int _val;
    Node* left;
    Node* right;
};

void TestSharePtr(){
    shared_ptr<Node> p1(new Node(10));
    cout << p1.get() << endl;
    shared_ptr<Node> p2(move(p1));
    cout << p2.get() <<  " " << p2.use_count() << endl;
    cout << p1.get() << endl;
}

int main(){
    TestSharePtr();
    return 0;
}