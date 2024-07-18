#include "BSTree.hpp"

void TestInsert(){
    BSTree<int> bst;
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    int b[] = {1,2,3,4,5,6,7,8,9,10};
    int c[] = {10,9,8,7,6,5,4,3,2,1,0};
    // for(auto e : a){
    //     bst.Insert(e);
    // // }
    for(auto e : a){
        bst.Insert(e);
    }
    BSTree<int> bt(bst);
    bt.Inorder();
    bst.Inorder();
}

int main(){
    TestInsert();
    return 0;
}