#include "AVLTree.hpp"

void TestAVLTree(){
    spigcoder::AVLTree<int, int> avl;
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for(const auto& e : a){
        avl.insert(make_pair(e, e));
    }
    avl.Inorder();
    cout << avl.IsBalance() << endl;
}

int main(){
    TestAVLTree();
    return 0;
}