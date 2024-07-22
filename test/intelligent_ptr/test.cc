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

}

int main(){
    TestSharePtr();
    return 0;
}