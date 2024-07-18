#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

/*BSTree是一个搜索二叉树，要求左边的孩子比它小，右边的孩子比它大，是一种特殊的二叉树*/
template<class K>
struct BSTNode
{
    BSTNode(K key = 0)
    :_left(nullptr),
    _right(nullptr),
    _key(key)
    {}

public:
    BSTNode* _right;
    BSTNode* _left;
    K _key;
};

template<class K>
class BSTree
{
private:
    using Node = BSTNode<K>;
public:
    BSTree(/* args */):_root(nullptr){};
    BSTree(const BSTree& tree) { 
        _root = new Node(tree._root->_key);
        _root->_left = Copy(tree._root->_left);
        _root->_right = Copy(tree._root->_right);
     }
    ~BSTree(){ DeStructor(_root); }
    BSTree& operator=(BSTree bst){
        swap(bst._root, _root);
        return *this;
    }
    void Inorder();
    bool Insert(const K& key);
    bool Erase(const K& key);
    void DeStructor(Node* node);
private:
    void _Inorder(Node* node);
    Node* Copy(const Node* node);
    Node* _root; 
};

template<class K>
typename BSTree<K>::Node* BSTree<K>::Copy(const Node* node){
    if(node == nullptr) return nullptr;

    Node* new_node = new Node(node->_key);
    new_node->_left = Copy(node->_left);
    new_node->_right = Copy(node->_right);

    return new_node;
} 

template<class K>
void BSTree<K>::DeStructor(Node* node){
    if(node == nullptr) return;
    DeStructor(node->_left);
    DeStructor(node->_right);
    delete node;
}

template<class K>
void BSTree<K>::Inorder(){
    _Inorder(_root);
    cout << endl;
}


template<class K>
void BSTree<K>::_Inorder(Node* node){
    if(node == nullptr) return;
    _Inorder(node->_left);
    cout << node->_key << " ";
    _Inorder(node->_right);
}

//注意参数的设置，对于这种不会改变的类型最好设置成为const &来减少拷贝构造的成本
template<class K>
bool BSTree<K>::Insert(const K& key){
    if(_root == nullptr){
        _root = new Node(key);
        return true;
    } 

    Node *cur = _root, *parent = nullptr;
    while(cur){
        parent = cur;
        if(key > cur->_key){ 
            cur = cur->_right;
        }else if(key < cur->_key){
            cur = cur->_left;
        }else{
            return false;
        }
    }
    //将cur插入到parent的指定位置
    assert(parent != nullptr);
    if(key > parent->_key) parent->_right = new Node(key);
    else parent->_left = new Node(key);
    return true;
}


template<class K>
bool BSTree<K>::Erase(const K& key){
    assert(_root);
    Node *cur = _root, *parent = nullptr;
    while(cur){
        if(key > cur->_key){
            parent = cur;
            cur = cur->_right;
        }else if(key < cur->_key){
            parent = cur;
            cur = cur->_left;
        }else{
            if(cur->_left == nullptr){
                if(parent == nullptr){
                    _root = cur->_right;
                }else{
                    if(cur == parent->_left) parent->_left = cur->_right;
                    if(cur == parent->_right) parent->_right = cur->_right; 
                }
                delete cur;
                return true;
            }else if(cur->_right == nullptr){
                if(parent == nullptr){
                    _root = cur->_left;
                }else{
                    //不要忘了删除cur
                    if(cur == parent->_left) parent->_left = cur->_left;
                    if(cur == parent->_right) parent->_right = cur->_left; 
                }
                delete cur;
                return true;
            }else{
                Node *right_min = cur->_right, *right_min_parent = cur;
                while(right_min->_left){
                    right_min_parent  = right_min;
                    right_min = right_min->_left;
                }
                if(right_min_parent == cur){
                    //第一个孩子就是最小的孩子的孩子应该挂在parent的左边
                    right_min_parent->_right = right_min->_right;
                }else{
                    right_min_parent->_left = right_min->_right;
                } 
                cur->_key = right_min->_key;
                delete right_min;
                return true; 
            }
        }
    } 
    return false;
}






















