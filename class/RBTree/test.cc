#include "RBTree.hpp"

void TestRBTree(){
    spigcoder::RBTree<int, int> avl;
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for(const auto& e : a){
        avl.insert(make_pair(e, e));
    }
    avl.Inorder();
    cout << avl.IsBalance();
}

int main(){
    TestRBTree();
    return 0;
}