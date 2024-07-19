#include "AVLTree.hpp"

void TestAVLTree(){
    spigcoder::AVLTree<int, int> avl;
    int a[] = {10, 20, 8, 30, 15, 17};
    for(const auto& e : a){
        avl.insert(make_pair(e, e));
    }
    avl.Inorder();
}

int main(){
    TestAVLTree();
    return 0;
}